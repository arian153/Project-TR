#include "Terrain.hpp"

#include "../../../Manager/Component/EngineComponent/TerrainComponent.hpp"
#include "../../Core/Utility/CoreUtility.hpp"
#include "../../Math/Utility/NoiseUtility.hpp"
#include "../Common/Buffer2/ConstantBufferCommon.hpp"
#include "../Common/Buffer2/ConstantBufferData.hpp"
#include "../Common/Buffer2/IndexBufferCommon.hpp"
#include "../Common/Buffer2/VertexBufferCommon.hpp"
#include "../DataType/MeshData.hpp"
#include "../Utility/MeshGenerator.hpp"
#include "Terrain/HitData.hpp"

namespace GAM400
{
    Terrain::Terrain()
    {
    }

    Terrain::~Terrain()
    {
    }

    void Terrain::Initialize()
    {
        CreateBuffer();
    }

    void Terrain::Update(Real dt)
    {
        m_component->Update(dt);
        //m_space.Update(dt);
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

    void Terrain::IsMousePressed(const Ray& ray) const
    {
        HitData hit_data(ray);
        m_terrain_space.CastRay(hit_data);

        if (hit_data.hit)
        {
            m_component->m_w_idx = hit_data.closest_idx % m_width_div;
            m_component->m_d_idx = hit_data.closest_idx / m_width_div;

            m_component->m_picking_point = hit_data.intersection;
            m_component->m_closest_point = m_grid.vertices[hit_data.closest_idx].GetPosition();
        }
    }

    void Terrain::IsMouseDown(const Ray& ray)
    {
    }

    void Terrain::CreateBuffer()
    {
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

    void Terrain::BuildBuffer()
    {
        size_t size = m_grid.vertices.size();
        m_terrain_space.Update();
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

    void Terrain::AddPerlinNoise()
    {
        Real half_width = m_terrain_width * 0.5f;
        Real half_depth = m_terrain_depth * 0.5f;

        size_t size = m_grid.vertices.size();

        for (size_t i = 0; i < size; ++i)
        {
            Vector3 p = m_grid.vertices[i].GetPosition();
            Vector3 d;
            p.y += m_perlin_noise_scale * m_noise_utility.Noise(
                                                                Vector3(
                                                                        (p.x + half_width) / m_perlin_noise_density,
                                                                        0.0f,
                                                                        (p.z + half_depth) / m_perlin_noise_density), d, m_smooth_level, m_b_noise_user_random);
            m_grid.vertices[i].SetPosition(p);
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
        for (size_t i = 0; i < size; ++i)
        {
            m_point_indices.emplace_back((U32)i);
        }

        for (auto& face : m_grid.faces)
        {
            //add adjacent faces
            m_point_indices[face.a].faces.emplace_back(face.a, face.b, face.c);
            m_point_indices[face.b].faces.emplace_back(face.a, face.b, face.c);
            m_point_indices[face.c].faces.emplace_back(face.a, face.b, face.c);
        }
    }

    void Terrain::SetNoiseSeed(U32 seed)
    {
        m_noise_utility.SetSeed(seed);
    }
}
