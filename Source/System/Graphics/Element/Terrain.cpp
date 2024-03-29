/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include "Terrain.hpp"

#include <fstream>

#include "../../../Manager/Component/EngineComponent/TerrainComponent.hpp"
#include "../../../Manager/Resource/ResourceType/TextResource.hpp"
#include "../../Core/Input/InputCommon.hpp"
#include "../../Core/Input/KeyboardInput.hpp"
#include "../../Core/Input/MouseInput.hpp"
#include "../../Core/Utility/CoreUtility.hpp"
#include "../../Core/Utility/TimeUtility.hpp"
#include "../../GUI/Editor/Command/CommandRegistry.hpp"
#include "../../GUI/Editor/Command/EditorCommand.hpp"
#include "../../Math/Structure/Transform.hpp"
#include "../../Math/Utility/NoiseUtility.hpp"
#include "../../Math/Utility/Utility.inl"
#include "../Common/Buffer2/ConstantBufferCommon.hpp"
#include "../Common/Buffer2/ConstantBufferData.hpp"
#include "../Common/Buffer2/IndexBufferCommon.hpp"
#include "../Common/Buffer2/VertexBufferCommon.hpp"
#include "../Common/Texture/TextureCommon.hpp"
#include "../DataType/MeshData.hpp"
#include "../Utility/MeshGenerator.hpp"
#include "Terrain/HitData.hpp"

namespace GAM400
{
    Terrain::Terrain()
        : m_edit_hit_data(Ray())
    {
    }

    Terrain::~Terrain()
    {
    }

    void Terrain::Initialize()
    {
        CreateBuffer();
        m_brush_size = 2.0f;
    }

    void Terrain::Update(Real dt)
    {
        m_component->Update(dt);
        if (m_input != nullptr)
        {
            if (m_input->GetMouseInput()->IsDown(eKeyCodeMouse::Right) == false)
            {
                m_edit_hit_data.hit = false;
            }
        }
    }

    void Terrain::Shutdown()
    {
        if (m_component != nullptr)
        {
            m_component->m_terrain = nullptr;
        }
        m_terrain_space.Shutdown();
        ReleaseBuffer();
    }

    void Terrain::Bind() const
    {
        m_vertex_buffer->Bind(0);
        m_index_buffer->Bind(0);
        m_textures.Bind();
        m_matrix_buffer->Bind();
        m_texture_buffer->Bind();
        m_material_buffer->Bind();
    }

    void Terrain::Draw() const
    {
        m_index_buffer->Draw();
    }

    void Terrain::IsMousePressed(const Ray& ray)
    {
        HitData hit_data(ray);
        m_terrain_space.CastRay(hit_data);

        if (hit_data.hit)
        {
            m_component->m_w_idx = hit_data.closest_idx % m_width_div;
            m_component->m_d_idx = hit_data.closest_idx / m_width_div;

            m_component->m_picking_point = hit_data.intersection;
            m_hit_vertex                 = m_grid.vertices[hit_data.closest_idx].GetPosition();
            m_component->m_closest_point = m_hit_vertex;

            auto& hit_face = hit_data.node->sub_terrain.faces[hit_data.face_idx];

            m_component->m_face_a = hit_face.idx_a;
            m_component->m_face_b = hit_face.idx_b;
            m_component->m_face_c = hit_face.idx_c;

            m_edit_hit_data = hit_data;

            if (m_input != nullptr)
            {
                auto mouse    = m_input->GetMouseInput();
                m_hit_mouse_y = mouse->CurrentPosition().y;
            }

            m_component->m_edit_grid = m_grid;
        }
    }

    void Terrain::IsMouseDown(const Ray& ray)
    {
        if (m_brush_mode == 0)
        {
            if (m_input != nullptr)
            {
                auto mouse    = m_input->GetMouseInput();
                auto keyboard = m_input->GetKeyboardInput();

                int curr_y = mouse->CurrentPosition().y;
                //int  prev_y = mouse->PreviousPosition().y;

                Vector3 new_pos = ray.position + ray.direction * m_edit_hit_data.t;

                Real dy = 0.01f * static_cast<Real>(m_hit_mouse_y - curr_y);

                if (mouse->IsDown(eKeyCodeMouse::Right))
                {
                    if (m_edit_hit_data.hit)
                    {
                        Vector3 pos = m_grid.vertices[m_edit_hit_data.closest_idx].GetPosition();
                        pos.y       = new_pos.y;//m_hit_vertex.y + dy;

                        m_grid.vertices[m_edit_hit_data.closest_idx].SetPosition(pos);
                        m_edit_hit_data.node->aabb.ExpandY(pos.y, pos.y);
                        m_edit_hit_data.node->sub_terrain.Update(m_grid);
                        //m_edit_hit_data.node->sub_terrain.faces[m_edit_hit_data.face_idx].SetVertex(m_edit_hit_data.closest_idx, pos);
                        m_terrain_space.UpdateAABBNode(m_edit_hit_data.node);
                        CalculateNTB(m_edit_hit_data.closest_idx);
                        BuildBuffer(false);
                        m_b_edit_down = true;
                    }
                }
            }
        }
        else if (m_brush_mode > 0)
        {
            HitData hit_data(ray);
            m_terrain_space.CastRay(hit_data);

            if (hit_data.hit)
            {
                m_component->m_picking_point = hit_data.intersection;
                m_brush.SetCenterHalfSize(hit_data.intersection, m_brush_size);

                m_hit_vertex   = m_grid.vertices[hit_data.closest_idx].GetPosition();
                auto& hit_face = hit_data.node->sub_terrain.faces[hit_data.face_idx];

                m_component->m_face_a = hit_face.idx_a;
                m_component->m_face_b = hit_face.idx_b;
                m_component->m_face_c = hit_face.idx_c;

                std::vector<SubTerrain*>  sub_terrains;
                std::vector<TerrainFace*> faces;

                Real addition = m_brush_mode == 1 ? m_brush_intensity : -m_brush_intensity;

                m_terrain_space.ApplyAddition(m_brush, sub_terrains, faces, addition);

                for (auto& sub_terrain : sub_terrains)
                {
                    for (auto& face : sub_terrain->faces)
                    {
                        CalculateNTB(face);
                    }
                }

                for (auto& face : faces)
                {
                    CalculateNTB(*face);
                }

                BuildBuffer(false);
                m_b_edit_down = true;
            }
        }
    }

    void Terrain::UpdatePicking(const Ray& ray)
    {
        if (m_b_edit_down == true)
        {
            m_terrain_space.Update();
            std::string message;

            if (m_brush_mode == 0)
            {
                message = "Edit Terrain Vertex";
            }
            else if (m_brush_mode == 1)
            {
                message = "Edit Terrain Using Piling Brush";
            }
            else if (m_brush_mode == 2)
            {
                message = "Edit Terrain Using Digging Brush";
            }

            m_command_registry->PushCommand(
                                            new EditFunction<
                                                MeshData,
                                                Terrain,
                                                &Terrain::SetGridData>(this, m_component->m_edit_grid, m_grid, message));

            m_b_edit_down = false;
        }

        HitData hit_data(ray);
        m_terrain_space.CastRay(hit_data);

        if (hit_data.hit)
        {
            m_component->m_w_idx = hit_data.closest_idx % m_width_div;
            m_component->m_d_idx = hit_data.closest_idx / m_width_div;

            m_component->m_picking_point = hit_data.intersection;
            m_hit_vertex                 = m_grid.vertices[hit_data.closest_idx].GetPosition();
            m_component->m_closest_point = m_hit_vertex;

            auto& hit_face = hit_data.node->sub_terrain.faces[hit_data.face_idx];

            m_component->m_face_a = hit_face.idx_a;
            m_component->m_face_b = hit_face.idx_b;
            m_component->m_face_c = hit_face.idx_c;

            m_edit_hit_data = hit_data;
        }
    }

    void Terrain::CreateBuffer()
    {
        if (m_height_map_texture == nullptr)
        {
            m_height_map_texture = new TextureCommon();
        }

        if (m_index_buffer == nullptr)
        {
            m_index_buffer = new IndexBufferCommon();
        }

        if (m_vertex_buffer == nullptr)
        {
            m_vertex_buffer = new VertexBufferCommon();
        }

        if (m_texture_buffer == nullptr)
        {
            m_texture_buffer = new ConstantBufferCommon();
            m_texture_buffer->Init(m_renderer, eBindingStage::PixelShader, sizeof(TextureBufferData), 0);
        }

        if (m_matrix_buffer == nullptr)
        {
            m_matrix_buffer = new ConstantBufferCommon();
            m_matrix_buffer->Init(m_renderer, eBindingStage::VertexShader, sizeof(MatrixBufferData), 0);
        }

        if (m_material_buffer == nullptr)
        {
            m_material_buffer = new ConstantBufferCommon();
            m_material_buffer->Init(m_renderer, eBindingStage::PixelShader, sizeof(MaterialBufferData), 3);
        }
    }

    void Terrain::ReleaseBuffer()
    {
        if (m_height_map_texture != nullptr)
        {
            m_height_map_texture->Shutdown();
            delete m_height_map_texture;
            m_height_map_texture = nullptr;
        }

        if (m_index_buffer != nullptr)
        {
            m_index_buffer->Shutdown();
            delete m_index_buffer;
            m_index_buffer = nullptr;
        }

        if (m_vertex_buffer != nullptr)
        {
            m_vertex_buffer->Shutdown();
            delete m_vertex_buffer;
            m_vertex_buffer = nullptr;
        }

        if (m_texture_buffer != nullptr)
        {
            m_texture_buffer->Shutdown();
            delete m_texture_buffer;
            m_texture_buffer = nullptr;
        }

        if (m_material_buffer != nullptr)
        {
            m_material_buffer->Shutdown();
            delete m_material_buffer;
            m_material_buffer = nullptr;
        }

        if (m_matrix_buffer != nullptr)
        {
            m_matrix_buffer->Shutdown();
            delete m_matrix_buffer;
            m_matrix_buffer = nullptr;
        }
    }

    void Terrain::BuildBuffer(bool update_space)
    {
        if (update_space)
        {
            m_terrain_space.Update();
        }

        size_t size = m_grid.vertices.size();
        if (m_terrain_vertex_size == size)
        {
            //update vertex buffer
            m_vertex_buffer->Update(m_grid.vertices);
        }
        else
        {
            //resize vertex & index buffer
            m_index_buffer->Shutdown();
            m_vertex_buffer->Shutdown();

            m_index_buffer->Init(m_renderer, m_grid.indices);
            m_vertex_buffer->Init(m_renderer, m_grid.vertices, true);
            m_terrain_vertex_size = size;
        }
    }

    std::string Terrain::ExportPPM(const std::string& root_path)
    {
        PixelData data;
        data.w = (U32)m_width_div;
        data.h = (U32)m_depth_div;

        size_t size    = (size_t)data.w * data.h;
        data.pixels    = new PixelData::PixelRGB[size];
        Real inv_scale = m_terrain_space.RootScaleY();
        inv_scale      = Math::IsZero(inv_scale) ? 0.0f : 1.0f / inv_scale;
        Real min       = m_terrain_space.RootMinY();

        for (size_t i = 0; i < size; ++i)
        {
            Vector3 p        = m_grid.vertices[i].GetPosition();
            Real    scale    = (p.y - min) * inv_scale;
            data.pixels[i].r = scale;
            data.pixels[i].g = scale;
            data.pixels[i].b = scale;
        }

        m_height_map_texture->Shutdown();
        m_height_map_texture_created = m_height_map_texture->Initialize(m_renderer, &data);

        std::string time_format = TimeUtility::GetCurrentTimeString();
        std::string file_name   = "\\TerrainHeightMap" + time_format + ".ppm";
        std::string file_path   = root_path + file_name;

        TextResource::SavePPM(&data, file_path);

        return file_path;
    }

    std::string Terrain::ExportOBJ(const std::string& root_path)
    {
        std::string   time_format = TimeUtility::GetCurrentTimeString();
        std::string   file_name   = "\\TerrainMesh" + time_format + ".obj";
        std::string   file_path   = root_path + file_name;
        std::ofstream ofs;
        ofs.open(file_path, std::ios_base::out);

        size_t vertex_count = m_grid.vertices.size();

        for (size_t i = 0; i < vertex_count; ++i)
        {
            Vector3 v = m_grid.vertices[i].GetPosition();
            ofs << "v " << v.x << " " << v.y << " " << -1.0f * v.z << std::endl;
        }

        for (size_t i = 0; i < vertex_count; ++i)
        {
            Vector2 vt = m_grid.vertices[i].GetUV();
            ofs << "vt " << vt.x << " " << 1.0f - vt.y << std::endl;
        }

        for (size_t i = 0; i < vertex_count; ++i)
        {
            Vector3 vn = m_grid.vertices[i].GetNormal();
            ofs << "vn " << vn.x << " " << vn.y << " " << -1.0f * vn.z << std::endl;
        }

        size_t face_count = m_grid.faces.size();

        for (size_t i = 0; i < face_count; ++i)
        {
            ofs << "f ";

            U32 fa = m_grid.faces[i].a + 1;
            U32 fb = m_grid.faces[i].b + 1;
            U32 fc = m_grid.faces[i].c + 1;

            ofs << fc << "/" << fc << "/" << fc << " ";
            ofs << fb << "/" << fb << "/" << fb << " ";
            ofs << fa << "/" << fa << "/" << fa << std::endl;
        }

        ofs.close();
        return file_path;
    }

    void Terrain::GenerateTrigonometric()
    {
        size_t size = m_grid.vertices.size();
        for (size_t i = 0; i < size; ++i)
        {
            Vector3 p = m_grid.vertices[i].GetPosition();
            p.y       = GenerateTrigonometricHeight(p.x, p.z);

            m_grid.vertices[i].SetPosition(p);
            m_grid.vertices[i].SetNormal(GenerateTrigonometricNormal(p.x, p.y));
            m_grid.vertices[i].CalculateTangentAndBinormal();
        }
    }

    Real Terrain::GenerateTrigonometricHeight(Real x, Real z) const
    {
        return m_trigonometric_factor_a * (z * sinf(m_trigonometric_factor_b * x) + x * cosf(m_trigonometric_factor_b * z));
    }

    Vector3 Terrain::GenerateTrigonometricNormal(Real x, Real z) const
    {
        Real ab = m_trigonometric_factor_a * m_trigonometric_factor_b;

        Vector3 normal(
                       -ab * z * cosf(m_trigonometric_factor_b * x) - m_trigonometric_factor_a * cosf(m_trigonometric_factor_b * z),
                       1.0f,
                       -m_trigonometric_factor_a * sinf(m_trigonometric_factor_b * x) + ab * x * sinf(m_trigonometric_factor_b * z));

        return normal.Unit();
    }

    void Terrain::ClearGrid()
    {
        MeshGenerator mesh_generator;
        mesh_generator.CreateGrid(m_terrain_width, m_terrain_depth, (U32)m_depth_div, (U32)m_width_div, m_grid);

        if (m_terrain_vertex_size != m_grid.vertices.size())
        {
            CalculateGridIndices();
            m_terrain_space.Initialize(this);
        }
    }

    void Terrain::GeneratePerlinNoise()
    {
        Real half_width = m_terrain_width * 0.5f;
        Real half_depth = m_terrain_depth * 0.5f;

        size_t size = m_grid.vertices.size();

        if (m_b_analytical_normal)
        {
            for (size_t i = 0; i < size; ++i)
            {
                Vector3 p = m_grid.vertices[i].GetPosition();
                Vector3 d;
                p.y = m_perlin_noise_scale * m_noise_utility.Noise(
                                                                   Vector3(
                                                                           (p.x + half_width) / m_perlin_noise_density,
                                                                           0.0f,
                                                                           (p.z + half_depth) / m_perlin_noise_density), d, m_smooth_level, m_b_noise_user_random);
                m_grid.vertices[i].SetPosition(p);
                m_grid.vertices[i].SetNormal(Vector3(-d.x, 1, -d.z).Unit());
                m_grid.vertices[i].SetTangent(Vector3(1, d.x, 0).Unit());
                m_grid.vertices[i].SetBinormal(Vector3(0, d.z, 1).Unit());
            }
        }
        else
        {
            for (size_t i = 0; i < size; ++i)
            {
                Vector3 p = m_grid.vertices[i].GetPosition();
                Vector3 d;
                p.y = m_perlin_noise_scale * m_noise_utility.Noise(
                                                                   Vector3(
                                                                           (p.x + half_width) / m_perlin_noise_density,
                                                                           0.0f,
                                                                           (p.z + half_depth) / m_perlin_noise_density), d, m_smooth_level, m_b_noise_user_random);
                m_grid.vertices[i].SetPosition(p);
            }
        }
    }

    void Terrain::AddTexture(TextureCommon* texture)
    {
        m_textures.PushBack(texture);
    }

    void Terrain::ClearTexture()
    {
        m_textures.Clear();
    }

    void Terrain::RemoveTexture(TextureCommon* texture)
    {
        m_textures.Erase(texture);
    }

    void Terrain::SetRenderer(RendererCommon* renderer)
    {
        m_renderer = renderer;
    }

    void Terrain::SetMaterialIdentifier(const MaterialIdentifier& material_data)
    {
        m_material = material_data;
        m_textures.Clear();

        //get actual resource data from resource manager.
        if (m_texture_buffer != nullptr)
        {
            TextureBufferData data;
            data.diff_type = m_material.diffuse_type;
            data.spec_type = m_material.specular_type;
            data.norm_type = m_material.normal_type;
            //E5_TODO : need to update user gamma setting
            data.gamma = 2.2f;

            m_texture_buffer->Update(data);
        }
    }

    void Terrain::SetMaterialColor(const MaterialColor& color_data)
    {
        m_mat_color = color_data;

        if (m_material_buffer != nullptr)
        {
            MaterialBufferData data;
            data.ambient  = m_mat_color.ambient;
            data.diffuse  = m_mat_color.diffuse;
            data.specular = m_mat_color.specular;
            data.reflect  = m_mat_color.reflect;

            m_material_buffer->Update(data);
        }
    }

    void Terrain::SetWorldMatrix(const Matrix44& world)
    {
        m_world = world;
    }

    void Terrain::UpdateMatrixBuffer(const Matrix44& view, const Matrix44& proj) const
    {
        MatrixBufferData mvp_buffer;
        mvp_buffer.world = m_world;
        mvp_buffer.view  = view;
        mvp_buffer.proj  = proj;
        m_matrix_buffer->Update(mvp_buffer);
    }

    void Terrain::UpdateMaterialBuffer() const
    {
        if (m_material_buffer != nullptr)
        {
            MaterialBufferData data;
            data.ambient  = m_mat_color.ambient;
            data.diffuse  = m_mat_color.diffuse;
            data.specular = m_mat_color.specular;
            data.reflect  = m_mat_color.reflect;

            m_material_buffer->Update(data);
        }
    }

    void Terrain::UpdateTextureBuffer() const
    {
        if (m_texture_buffer != nullptr)
        {
            TextureBufferData data;
            data.diff_type = m_material.diffuse_type;
            data.spec_type = m_material.specular_type;
            data.norm_type = m_material.normal_type;
            data.gamma     = 2.2f;

            m_texture_buffer->Update(data);
        }
    }

    std::string Terrain::GetShaderType() const
    {
        return m_material.shader_type;
    }

    void Terrain::CalculateNTB()
    {
        //Calculate Vertex Normal
        std::vector<Vector3> normals;
        Vector3              accumulated_normal;
        for (auto& point : m_point_indices)
        {
            normals.clear();
            accumulated_normal.SetZero();
            for (auto& face : point.faces)
            {
                Vector3 normal = m_grid.GetFaceNormal(face.a, face.b, face.c);
                auto    found  = std::find(normals.begin(), normals.end(), normal);
                if (found == normals.end())
                {
                    accumulated_normal += normal;
                    normals.push_back(normal);
                }
            }
            m_grid.vertices[point.index].SetNormal(accumulated_normal.Normalize());
            m_grid.vertices[point.index].CalculateTangentAndBinormal();
        }
    }

    void Terrain::CalculateGridIndices()
    {
        size_t size = m_grid.vertices.size();
        m_point_indices.clear();
        m_point_indices.resize(size);

        for (auto& face : m_grid.faces)
        {
            //add adjacent faces
            m_point_indices[face.a].index = face.a;
            m_point_indices[face.b].index = face.b;
            m_point_indices[face.c].index = face.c;
            m_point_indices[face.a].faces.emplace_back(face.a, face.b, face.c);
            m_point_indices[face.b].faces.emplace_back(face.a, face.b, face.c);
            m_point_indices[face.c].faces.emplace_back(face.a, face.b, face.c);
        }
    }

    void Terrain::SetNoiseSeed(U32 seed)
    {
        m_noise_utility.SetSeed(seed);
    }

    void Terrain::CalculateNTB(U32 idx)
    {
        //Calculate Vertex Normal
        std::vector<Vector3> normals;
        Vector3              accumulated_normal;
        std::set<U32>        updated_indices;

        if (idx < m_point_indices.size())
        {
            updated_indices.insert(idx);
            for (auto& face : m_point_indices[idx].faces)
            {
                updated_indices.insert(face.a);
                updated_indices.insert(face.b);
                updated_indices.insert(face.c);
            }

            normals.clear();
            accumulated_normal.SetZero();

            for (auto& updated_idx : updated_indices)
            {
                normals.clear();
                accumulated_normal.SetZero();

                for (auto& face : m_point_indices[updated_idx].faces)
                {
                    Vector3 normal = m_grid.GetFaceNormal(face.a, face.b, face.c);
                    auto    found  = std::find(normals.begin(), normals.end(), normal);
                    if (found == normals.end())
                    {
                        accumulated_normal += normal;
                        normals.push_back(normal);
                    }
                }
                m_grid.vertices[updated_idx].SetNormal(accumulated_normal.Normalize());
                m_grid.vertices[updated_idx].CalculateTangentAndBinormal();
            }
        }
    }

    void Terrain::CalculateNTB(const TerrainFace& updated_face)
    {
        //Calculate Vertex Normal
        std::vector<Vector3> normals;
        Vector3              accumulated_normal;
        std::set<U32>        updated_indices;

        updated_indices.insert(updated_face.idx_a);
        updated_indices.insert(updated_face.idx_b);
        updated_indices.insert(updated_face.idx_c);

        for (auto& face : m_point_indices[updated_face.idx_a].faces)
        {
            updated_indices.insert(face.a);
            updated_indices.insert(face.b);
            updated_indices.insert(face.c);
        }
        for (auto& face : m_point_indices[updated_face.idx_b].faces)
        {
            updated_indices.insert(face.a);
            updated_indices.insert(face.b);
            updated_indices.insert(face.c);
        }
        for (auto& face : m_point_indices[updated_face.idx_c].faces)
        {
            updated_indices.insert(face.a);
            updated_indices.insert(face.b);
            updated_indices.insert(face.c);
        }

        normals.clear();
        accumulated_normal.SetZero();

        for (auto& updated_idx : updated_indices)
        {
            normals.clear();
            accumulated_normal.SetZero();

            for (auto& face : m_point_indices[updated_idx].faces)
            {
                Vector3 normal = m_grid.GetFaceNormal(face.a, face.b, face.c);
                auto    found  = std::find(normals.begin(), normals.end(), normal);
                if (found == normals.end())
                {
                    accumulated_normal += normal;
                    normals.push_back(normal);
                }
            }
            m_grid.vertices[updated_idx].SetNormal(accumulated_normal.Normalize());
            m_grid.vertices[updated_idx].CalculateTangentAndBinormal();
        }
    }

    void Terrain::SetCommandRegistry(CommandRegistry* command_registry)
    {
        m_command_registry = command_registry;
    }

    void Terrain::SetMaterialAmbient(const Color& color)
    {
        m_mat_color.ambient = color;
        UpdateMaterialBuffer();
    }

    void Terrain::SetMaterialDiffuse(const Color& color)
    {
        m_mat_color.diffuse = color;
        UpdateMaterialBuffer();
    }

    void Terrain::SetMaterialSpecular(const Color& color)
    {
        m_mat_color.specular = color;
        UpdateMaterialBuffer();
    }

    void Terrain::SetGridData(const MeshData& grid_data)
    {
        m_grid = grid_data;
        m_terrain_space.Update();
        BuildBuffer();
    }

    void Terrain::SetTerrainWidth(const EditGridReal& width)
    {
        m_terrain_width = width.value;
        m_grid          = width.grid;
        m_terrain_space.Update();
        BuildBuffer();
    }

    void Terrain::SetTerrainDepth(const EditGridReal& depth)
    {
        m_terrain_depth = depth.value;
        m_grid          = depth.grid;
        m_terrain_space.Update();
        BuildBuffer();
    }

    void Terrain::SetTerrainWidthLOD(const EditGridI32& w_lod)
    {
        m_width_div = w_lod.value;
        m_grid      = w_lod.grid;
        m_terrain_space.Update();
        BuildBuffer();
    }

    void Terrain::SetTerrainDepthLOD(const EditGridI32& d_lod)
    {
        m_depth_div = d_lod.value;
        m_grid      = d_lod.grid;
        m_terrain_space.Update();
        BuildBuffer();
    }

    void Terrain::SetTerrainTriA(const EditGridReal& data)
    {
        m_trigonometric_factor_a = data.value;
        m_grid                   = data.grid;
        m_terrain_space.Update();
        BuildBuffer();
    }

    void Terrain::SetTerrainTriB(const EditGridReal& data)
    {
        m_trigonometric_factor_b = data.value;
        m_grid                   = data.grid;
        m_terrain_space.Update();
        BuildBuffer();
    }

    void Terrain::SetTerrainPerS(const EditGridReal& data)
    {
        m_perlin_noise_scale = data.value;
        m_grid               = data.grid;
        m_terrain_space.Update();
        BuildBuffer();
    }

    void Terrain::SetTerrainPerD(const EditGridReal& data)
    {
        m_perlin_noise_density = data.value;
        m_grid                 = data.grid;
        m_terrain_space.Update();
        BuildBuffer();
    }

    void Terrain::SetTerrainHMS(const EditGridReal& data)
    {
        m_height_map_scale = data.value;
        m_grid             = data.grid;
        m_terrain_space.Update();
        BuildBuffer();
    }
}
