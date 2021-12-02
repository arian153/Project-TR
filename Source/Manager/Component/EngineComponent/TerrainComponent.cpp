#include "TerrainComponent.hpp"

#include "TransformComponent.hpp"
#include "../../../External/JSONCPP/json/json.h"
#include "../../../System/Core/Utility/CoreUtility.hpp"
#include "../../../System/Graphics/Common/Texture/TextureCommon.hpp"
#include "../../../System/Graphics/Element/Scene.hpp"
#include "../../../System/Graphics/Element/Terrain.hpp"
#include "../../../System/Graphics/Utility/PrimitiveRenderer.hpp"
#include "../../../System/GUI/Editor/Command/CommandRegistry.hpp"
#include "../../../System/GUI/Editor/Command/EditorCommand.hpp"
#include "../../../System/Logic/LogicSubsystem.hpp"
#include "../../Object/Object.hpp"
#include "../../Resource/ResourceManager.hpp"
#include "../../Resource/ResourceType/JsonResource.hpp"
#include "../../Resource/ResourceType/TextResource.hpp"
#include "../../Resource/ResourceType/TextureResource.hpp"
#include "../../Space/Space.hpp"

namespace GAM400
{
    TerrainComponent::~TerrainComponent()
    {
    }

    void TerrainComponent::Initialize()
    {
        if (m_terrain == nullptr)
        {
            m_terrain = new Terrain();
            Subscribe();
            m_terrain->Initialize();
            m_terrain->SetNoiseSeed(m_noise_seed);
            m_terrain->ClearGrid();
            m_terrain->GeneratePerlinNoise();
            m_terrain->CalculateNTB();
            m_terrain->BuildBuffer();

            m_terrain->m_input     = m_space->GetLogicSubsystem()->GetInput();
            m_terrain->m_component = this;

            if (m_owner->HasComponent<TransformComponent>())
            {
                m_terrain->m_transform = m_owner->GetComponent<TransformComponent>()->GetTransform();
            }
        }

        m_drawing_sphere.radius = 0.1f;
    }

    void TerrainComponent::Update(Real dt)
    {
        Matrix44 world = Matrix44::Identity();
        if (m_owner->HasComponent<TransformComponent>())
        {
            world = m_owner->GetComponent<TransformComponent>()->GetTransformMatrix();
        }

        m_terrain->SetWorldMatrix(world);

        if (m_terrain->m_edit_hit_data.hit)
        {
            auto primitive_renderer = m_space->GetScene()->GetPrimitiveRenderer();

            Vector3 closest = m_terrain->m_grid.vertices[m_terrain->m_edit_hit_data.closest_idx].GetPosition();

            if (m_terrain->m_brush_mode == 0)
            {
                primitive_renderer->DrawPrimitiveInstancing(m_drawing_sphere, Quaternion(), m_picking_point, eRenderingMode::Face, Color(0, 0, 0, 1));
                primitive_renderer->DrawPrimitiveInstancing(m_drawing_sphere, Quaternion(), closest, eRenderingMode::Face, Color(0, 1, 0, 1));

                Vector3 face_a = m_terrain->m_grid.vertices[m_face_a].GetPosition();
                Vector3 face_b = m_terrain->m_grid.vertices[m_face_b].GetPosition();
                Vector3 face_c = m_terrain->m_grid.vertices[m_face_c].GetPosition();

                primitive_renderer->DrawPrimitiveInstancing(m_drawing_sphere, Quaternion(), face_a, eRenderingMode::Face, Color(1, 0, 0, 1));
                primitive_renderer->DrawPrimitiveInstancing(m_drawing_sphere, Quaternion(), face_b, eRenderingMode::Face, Color(1, 0, 0, 1));
                primitive_renderer->DrawPrimitiveInstancing(m_drawing_sphere, Quaternion(), face_c, eRenderingMode::Face, Color(1, 0, 0, 1));
            }
            else
            {
                m_drawing_box.position = m_picking_point;
                m_drawing_box.SetBox(m_terrain->m_brush_size.x, m_terrain->m_brush_size.y, m_terrain->m_brush_size.z);
                primitive_renderer->DrawPrimitive(m_drawing_box, eRenderingMode::Face, Color(0, 1, 0, 0.1f));
            }
        }
    }

    void TerrainComponent::Shutdown()
    {
        Unsubscribe();
        if (m_terrain != nullptr)
        {
            m_terrain->Shutdown();
            delete m_terrain;
            m_terrain = nullptr;
        }
    }

    bool TerrainComponent::Load(const Json::Value& data)
    {
        if (JsonResource::HasMember(data, "Shader Type"))
        {
            m_material_identifier.shader_type = data["Shader Type"].asString();
        }
        else
        {
            //E5_TODO : need to update default shader name.
            m_material_identifier.shader_type = "Default";
        }

        if (JsonResource::HasMember(data, "Texture"))
        {
            auto texture_data = data["Texture"];

            if (JsonResource::HasMember(texture_data, "Diffuse") && texture_data["Diffuse"].isArray())
            {
                int idx = 0;
                for (auto it = texture_data["Diffuse"].begin(); it != texture_data["Diffuse"].end(); ++it)
                {
                    if ((*it).isString())
                    {
                        if (idx == 0)
                        {
                            m_material_identifier.diffuse0 = (*it).asString();
                        }
                        if (idx == 1)
                        {
                            m_material_identifier.diffuse1 = (*it).asString();
                        }
                        if (idx == 2)
                        {
                            m_material_identifier.diffuse2 = (*it).asString();
                        }
                    }
                    idx++;
                }
            }

            if (JsonResource::HasMember(texture_data, "Diffuse0"))
            {
                if (texture_data["Diffuse0"].isString())
                {
                    m_material_identifier.diffuse0 = texture_data["Diffuse0"].asString();
                }
            }

            if (JsonResource::HasMember(texture_data, "Diffuse1"))
            {
                if (texture_data["Diffuse1"].isString())
                {
                    m_material_identifier.diffuse1 = texture_data["Diffuse1"].asString();
                }
            }

            if (JsonResource::HasMember(texture_data, "Diffuse2"))
            {
                if (texture_data["Diffuse2"].isString())
                {
                    m_material_identifier.diffuse2 = texture_data["Diffuse2"].asString();
                }
            }

            if (JsonResource::HasMember(texture_data, "DiffuseType"))
            {
                if (texture_data["DiffuseType"].isString())
                {
                    std::string type = texture_data["DiffuseType"].asString();
                    if (type == "Texture")
                    {
                        m_material_identifier.diffuse_type = 1;
                    }
                    else if (type == "AlphaMapping")
                    {
                        m_material_identifier.diffuse_type = 2;
                    }
                    else if (type == "LightMapping")
                    {
                        m_material_identifier.diffuse_type = 3;
                    }
                    else if (type == "Multi-Texture")
                    {
                        m_material_identifier.diffuse_type = 4;
                    }
                    else
                    {
                        m_material_identifier.diffuse_type = 0;
                    }
                }
            }

            if (JsonResource::HasMember(texture_data, "Specular"))
            {
                if (texture_data["Specular"].isString())
                {
                    m_material_identifier.specular0     = texture_data["Specular"].asString();
                    m_material_identifier.specular_type = 1;
                }
                else
                {
                    m_material_identifier.specular_type = 0;
                }
            }
            else
            {
                m_material_identifier.specular_type = 0;
            }

            if (JsonResource::HasMember(texture_data, "NormalMap"))
            {
                if (texture_data["NormalMap"].isString())
                {
                    m_material_identifier.normal0     = texture_data["NormalMap"].asString();
                    m_material_identifier.normal_type = 1;
                }
                else
                {
                    m_material_identifier.normal_type = 0;
                }
            }
            else
            {
                m_material_identifier.normal_type = 0;
            }
        }

        if (JsonResource::HasMember(data, "Color"))
        {
            auto color_data = data["Color"];

            if (JsonResource::IsColor(color_data["Ambient"]))
            {
                m_material_color.ambient = JsonResource::AsColor(color_data["Ambient"]);
            }

            if (JsonResource::IsColor(color_data["Diffuse"]))
            {
                m_material_color.diffuse = JsonResource::AsColor(color_data["Diffuse"]);
            }

            if (JsonResource::IsColor(color_data["Specular"]))
            {
                m_material_color.specular = JsonResource::AsColor(color_data["Specular"]);
            }
        }

        m_terrain->SetMaterialIdentifier(m_material_identifier);
        m_terrain->SetMaterialColor(m_material_color);

        //diffuse texture0
        if (m_material_identifier.diffuse0 != "")
        {
            m_terrain->AddTexture(m_space->GetResourceManager()->GetTextureResource(ToWString(m_material_identifier.diffuse0))->GetTexture());
        }
        else
        {
            m_terrain->AddTexture(m_space->GetResourceManager()->GetTextureResource(L"DefaultTexture")->GetTexture());
        }
        //diffuse texture1
        if (m_material_identifier.diffuse1 != "")
        {
            m_terrain->AddTexture(m_space->GetResourceManager()->GetTextureResource(ToWString(m_material_identifier.diffuse1))->GetTexture());
        }
        else
        {
            m_terrain->AddTexture(m_space->GetResourceManager()->GetTextureResource(L"DefaultTexture")->GetTexture());
        }
        //diffuse texture2
        if (m_material_identifier.diffuse2 != "")
        {
            m_terrain->AddTexture(m_space->GetResourceManager()->GetTextureResource(ToWString(m_material_identifier.diffuse2))->GetTexture());
        }
        else
        {
            m_terrain->AddTexture(m_space->GetResourceManager()->GetTextureResource(L"DefaultTexture")->GetTexture());
        }
        //specular texture
        if (m_material_identifier.specular0 != "")
        {
            m_terrain->AddTexture(m_space->GetResourceManager()->GetTextureResource(ToWString(m_material_identifier.specular0))->GetTexture());
        }
        else
        {
            m_terrain->AddTexture(m_space->GetResourceManager()->GetTextureResource(L"DefaultTexture")->GetTexture());
        }
        //normal texture
        if (m_material_identifier.normal0 != "")
        {
            m_terrain->AddTexture(m_space->GetResourceManager()->GetTextureResource(ToWString(m_material_identifier.normal0))->GetTexture());
        }
        else
        {
            m_terrain->AddTexture(m_space->GetResourceManager()->GetTextureResource(L"DefaultTexture")->GetTexture());
        }

        m_height_maps.clear();
        m_space->GetResourceManager()->GetTextResources(".ppm", m_height_maps);
        m_height_map_idx = -1;
        m_height_map_names.clear();
        for (auto& resource : m_height_maps)
        {
            std::string name = resource->FileName() + resource->FileType();
            m_height_map_names.push_back(name);
        }

        return true;
    }

    void TerrainComponent::Save(Json::Value& data) const
    {
    }

    void TerrainComponent::Edit(CommandRegistry* command_registry)
    {
        if (ImGui::CollapsingHeader(m_type.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Text("Material");
            Color color = m_terrain->m_mat_color.ambient;
            ImGui::Text("Material - Ambient");
            ImGui::ColorEdit4("##Material - Ambient", &m_terrain->m_mat_color.ambient.r);
            if (ImGui::IsItemActivated())
            {
                m_material_color.ambient = color;
            }
            if (ImGui::IsItemDeactivatedAfterEdit())
            {
                std::string message = "Change Material Ambient";
                command_registry->PushCommand(
                                              new EditFunction<
                                                  Color,
                                                  Terrain,
                                                  &Terrain::SetMaterialAmbient>(m_terrain, m_material_color.ambient, m_terrain->m_mat_color.ambient, message));
            }

            ImGui::Text("Material - Diffuse");
            color = m_terrain->m_mat_color.diffuse;
            ImGui::ColorEdit4("##Material - Diffuse", &m_terrain->m_mat_color.diffuse.r);
            if (ImGui::IsItemActivated())
            {
                m_material_color.diffuse = color;
            }
            if (ImGui::IsItemDeactivatedAfterEdit())
            {
                std::string message = "Change Material Diffuse";
                command_registry->PushCommand(
                                              new EditFunction<
                                                  Color,
                                                  Terrain,
                                                  &Terrain::SetMaterialDiffuse>(m_terrain, m_material_color.diffuse, m_terrain->m_mat_color.diffuse, message));
            }

            ImGui::Text("Material - Specular");
            color = m_terrain->m_mat_color.specular;
            ImGui::ColorEdit4("##Material - Specular", &m_terrain->m_mat_color.specular.r);
            if (ImGui::IsItemActivated())
            {
                m_material_color.specular = color;
            }
            if (ImGui::IsItemDeactivatedAfterEdit())
            {
                std::string message = "Change Material Specular";
                command_registry->PushCommand(
                                              new EditFunction<
                                                  Color,
                                                  Terrain,
                                                  &Terrain::SetMaterialSpecular>(m_terrain, m_material_color.specular, m_terrain->m_mat_color.specular, message));
            }
            ImGui::Separator();
            ImGui::NewLine();
            ImGui::Text("Terrain");

            if (ImGui::Button("Clear Terrain"))
            {
                m_edit_grid = m_terrain->m_grid;
                m_terrain->ClearGrid();

                std::string message = "Clear Terrain Grid";
                command_registry->PushCommand(
                                              new EditFunction<
                                                  MeshData,
                                                  Terrain,
                                                  &Terrain::SetGridData>(m_terrain, m_edit_grid, m_terrain->m_grid, message));
            }

            if (ImGui::Button("Export Wavefront OBJ"))
            {
                m_terrain->ExportOBJ();
            }

            if (ImGui::Button("Export Height Map"))
            {
                m_terrain->ExportPPM();
            }

            if (m_terrain->m_height_map_texture_created)
            {
                ImVec2 uv_min      = ImVec2(0.0f, 0.0f);                   // Top-left
                ImVec2 uv_max      = ImVec2(1.0f, 1.0f);                   // Lower-right
                ImVec4 tint_col    = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // No tint
                ImVec4 border_col  = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white
                ImVec2 min         = ImGui::GetWindowContentRegionMin();
                ImVec2 max         = ImGui::GetWindowContentRegionMax();
                Real   scene_scale = max.x - min.x;
                Real   ratio       = (Real)m_terrain->m_depth_div / (Real)m_terrain->m_width_div;
                ImVec2 size        = ImVec2(scene_scale, scene_scale * ratio);
                ImGui::Image(
                             m_terrain->m_height_map_texture->GetTexture(), size
                           , uv_min, uv_max, tint_col, border_col);
            }

            ImGui::RadioButton("Vertex", &m_terrain->m_brush_mode, 0);
            ImGui::RadioButton("Piling Brush", &m_terrain->m_brush_mode, 1);
            ImGui::RadioButton("Digging Brush", &m_terrain->m_brush_mode, 2);

            if (m_terrain->m_brush_mode > 0)
            {
                ImGui::Text("Brush Size");
                if (ImGui::SliderFloat("##BrushSize", &m_terrain->m_brush_size.x, 1.0f, 10.0f))
                {
                    m_terrain->m_brush_size.y = m_terrain->m_brush_size.x;
                    m_terrain->m_brush_size.z = m_terrain->m_brush_size.x;
                }

                ImGui::Text("Brush Intensity");
            }

            ImGui::Text("Terrain Generation Method");
            const char* terrain_gen[] = {"Height-Map", "Trigonometric", "Perlin-Noise"};

            int prev = m_terrain_mode;
            if (ImGui::Combo("##Terrain Generation Mode", &m_terrain_mode, terrain_gen, 3))
            {
                m_edit_grid = m_terrain->m_grid;
                if (m_terrain_mode == 0)
                {
                    if (m_height_map_idx != -1)
                    {
                        auto resource = m_height_maps[m_height_map_idx];

                        auto pixel_data = resource->GetPixelData();
                        if (pixel_data != nullptr)
                        {
                            U32 width = pixel_data->w;
                            U32 depth = pixel_data->h;

                            m_terrain->m_terrain_width = (Real)width;
                            m_terrain->m_terrain_depth = (Real)depth;
                            m_terrain->m_width_div     = (I32)width;
                            m_terrain->m_depth_div     = (I32)depth;
                            m_terrain->ClearGrid();

                            for (U32 w = 0; w < width; ++w)
                            {
                                for (U32 d = 0; d < depth; ++d)
                                {
                                    U32     i     = d * width + w;
                                    Vector3 p     = m_terrain->m_grid.vertices[i].GetPosition();
                                    Real    scale = pixel_data->pixels[i].r;
                                    p.y           = (scale * 2.0f - 1.0f) * m_terrain->m_height_map_scale;
                                    m_terrain->m_grid.vertices[i].SetPosition(p);
                                }
                            }

                            m_terrain->CalculateNTB();
                        }
                    }
                }
                else if (m_terrain_mode == 1)
                {
                    m_terrain->ClearGrid();
                    m_terrain->GenerateTrigonometric();
                }
                else if (m_terrain_mode == 2)
                {
                    m_terrain->ClearGrid();
                    m_terrain->GeneratePerlinNoise();
                    m_terrain->CalculateNTB();
                }

                std::string message = "Change  Terrain Generation Method : " + std::string(terrain_gen[prev]) + " To " + std::string(terrain_gen[m_terrain_mode]);
                command_registry->PushCommand(
                                              new EditFunction<
                                                  MeshData,
                                                  Terrain,
                                                  &Terrain::SetGridData>(m_terrain, m_edit_grid, m_terrain->m_grid, message));
            }

            if (m_terrain_mode > 0)
            {
                ImGui::Text("Terrain Width");
                Real prev_vector1 = m_terrain->m_terrain_width;
                ImGui::InputFloat("##Terrain Width", &m_terrain->m_terrain_width);
                if (ImGui::IsItemActivated())
                {
                    m_edit_grid  = m_terrain->m_grid;
                    m_edit_width = prev_vector1;
                }
                if (ImGui::IsItemEdited())
                {
                    m_terrain->m_terrain_width = Math::Clamp(m_terrain->m_terrain_width, 1.0f, 1000.0f);
                    m_terrain->ClearGrid();
                    if (m_terrain_mode == 1)
                        m_terrain->GenerateTrigonometric();
                    else if (m_terrain_mode == 2)
                    {
                        m_terrain->GeneratePerlinNoise();
                        m_terrain->CalculateNTB();
                    }
                }
                if (ImGui::IsItemDeactivatedAfterEdit())
                {
                    std::string  message = "Change Terrain Width";
                    EditGridReal prev_edit(m_edit_grid);
                    prev_edit.value = m_edit_width;
                    EditGridReal next_edit(m_terrain->m_grid);
                    next_edit.value = m_terrain->m_terrain_width;

                    command_registry->PushCommand(
                                                  new EditFunction<
                                                      EditGridReal,
                                                      Terrain,
                                                      &Terrain::SetTerrainWidth>(m_terrain, prev_edit, next_edit, message));
                }

                ImGui::Text("Terrain Depth");
                if (ImGui::InputFloat("##Terrain Depth", &m_terrain->m_terrain_depth))
                {
                    m_terrain->m_terrain_depth = Math::Clamp(m_terrain->m_terrain_depth, 1.0f, 1000.0f);
                    m_terrain->ClearGrid();
                    if (m_terrain_mode == 1)
                        m_terrain->GenerateTrigonometric();
                    else if (m_terrain_mode == 2)
                    {
                        m_terrain->GeneratePerlinNoise();
                        m_terrain->CalculateNTB();
                    }
                    m_terrain->BuildBuffer();
                }

                ImGui::Text("Width LOD");
                if (ImGui::InputInt("##LOD Width", &m_terrain->m_width_div))
                {
                    m_terrain->m_width_div = Math::Clamp(m_terrain->m_width_div, 1, 500);
                    m_terrain->ClearGrid();
                    if (m_terrain_mode == 1)
                        m_terrain->GenerateTrigonometric();
                    else if (m_terrain_mode == 2)
                    {
                        m_terrain->GeneratePerlinNoise();
                        m_terrain->CalculateNTB();
                    }
                    m_terrain->BuildBuffer();
                }

                ImGui::Text("Depth LOD");
                if (ImGui::InputInt("##LOD Depth", &m_terrain->m_depth_div))
                {
                    m_terrain->m_depth_div = Math::Clamp(m_terrain->m_depth_div, 1, 500);
                    m_terrain->ClearGrid();
                    if (m_terrain_mode == 1)
                        m_terrain->GenerateTrigonometric();
                    else if (m_terrain_mode == 2)
                    {
                        m_terrain->GeneratePerlinNoise();
                        m_terrain->CalculateNTB();
                    }

                    m_terrain->BuildBuffer();
                }
            }

            if (m_terrain_mode == 1)
            {
                ImGui::Text("Trigonometric Scale");
                if (ImGui::SliderFloat("##Terrain Trigonometric A", &m_terrain->m_trigonometric_factor_a, -1.0f, 1.0f))
                {
                    //m_terrain->m_width_div = Math::Max(m_terrain->m_width_div, 1);
                    m_terrain->GenerateTrigonometric();
                    m_terrain->BuildBuffer();
                }

                ImGui::Text("Trigonometric Density");
                if (ImGui::SliderFloat("##Terrain Trigonometric B", &m_terrain->m_trigonometric_factor_b, -0.3f, 0.3f))
                {
                    //m_terrain->m_width_div = Math::Max(m_terrain->m_width_div, 1);
                    m_terrain->GenerateTrigonometric();
                    m_terrain->BuildBuffer();
                }
            }

            else if (m_terrain_mode == 2)
            {
                ImGui::Separator();
                ImGui::Text("Perlin Noise Scale");
                if (ImGui::SliderFloat("##Perlin Noise Scale", &m_terrain->m_perlin_noise_scale, 1.0f, 400.0f))
                {
                    m_terrain->GeneratePerlinNoise();
                    m_terrain->CalculateNTB();
                    m_terrain->BuildBuffer();
                }

                ImGui::Text("Perlin Noise Density");
                if (ImGui::SliderFloat("##Perlin Noise Density", &m_terrain->m_perlin_noise_density, 1.0f, 400.0f))
                {
                    m_terrain->GeneratePerlinNoise();
                    m_terrain->CalculateNTB();
                    m_terrain->BuildBuffer();
                }

                ImGui::Text("Interpolation Mode");
                const char* interpolation_mode[] = {"Smooth Order Linear", "Smooth Order Cubic", "Smooth Order Quintic", "Smooth Order Septic"};

                if (ImGui::Combo("##Interpolation Mode", &m_terrain->m_smooth_level, interpolation_mode, 4))
                {
                    m_terrain->GeneratePerlinNoise();
                    m_terrain->CalculateNTB();
                    m_terrain->BuildBuffer();
                }

                if (ImGui::Checkbox("Use Random Seed##RandOrPerm", &m_terrain->m_b_noise_user_random))
                {
                    m_terrain->GeneratePerlinNoise();
                    m_terrain->CalculateNTB();
                    m_terrain->BuildBuffer();
                }

                if (m_terrain->m_b_noise_user_random)
                {
                    ImGui::Text("Noise Seed");
                    if (ImGui::SliderInt("##Slider Seed", (int*)&m_noise_seed, 0, 999999))
                    {
                        m_terrain->SetNoiseSeed(m_noise_seed);
                        m_terrain->GeneratePerlinNoise();
                        m_terrain->CalculateNTB();
                        m_terrain->BuildBuffer();
                    }
                }
            }
            else if (m_terrain_mode == 0)
            {
                ImGui::Text("Height Map");

                int height_map_count = (int)m_height_map_names.size();

                if (ImGui::Combo("##Height Map Select", &m_height_map_idx, VectorStringGetter, (void*)&m_height_map_names, height_map_count))
                {
                    auto resource = m_height_maps[m_height_map_idx];

                    auto pixel_data = resource->GetPixelData();
                    if (pixel_data != nullptr)
                    {
                        U32 width = pixel_data->w;
                        U32 depth = pixel_data->h;

                        m_terrain->m_terrain_width = (Real)width;
                        m_terrain->m_terrain_depth = (Real)depth;
                        m_terrain->m_width_div     = (I32)width;
                        m_terrain->m_depth_div     = (I32)depth;
                        m_terrain->ClearGrid();

                        for (U32 w = 0; w < width; ++w)
                        {
                            for (U32 d = 0; d < depth; ++d)
                            {
                                U32     i     = d * width + w;
                                Vector3 p     = m_terrain->m_grid.vertices[i].GetPosition();
                                Real    scale = pixel_data->pixels[i].r;
                                p.y           = (scale * 2.0f - 1.0f) * m_terrain->m_height_map_scale;
                                m_terrain->m_grid.vertices[i].SetPosition(p);
                            }
                        }

                        m_terrain->CalculateNTB();
                        m_terrain->BuildBuffer();
                    }
                }

                ImGui::Text("Height Map Scale");
                if (ImGui::SliderFloat("##Height Map Scale", &m_terrain->m_height_map_scale, 1.0f, 400.0f))
                {
                    auto resource = m_height_maps[m_height_map_idx];

                    auto pixel_data = resource->GetPixelData();
                    if (pixel_data != nullptr)
                    {
                        U32 width = pixel_data->w;
                        U32 depth = pixel_data->h;

                        m_terrain->m_terrain_width = (Real)width;
                        m_terrain->m_terrain_depth = (Real)depth;
                        m_terrain->m_width_div     = (I32)width;
                        m_terrain->m_depth_div     = (I32)depth;
                        m_terrain->ClearGrid();

                        for (U32 w = 0; w < width; ++w)
                        {
                            for (U32 d = 0; d < depth; ++d)
                            {
                                U32     i     = d * width + w;
                                Vector3 p     = m_terrain->m_grid.vertices[i].GetPosition();
                                Real    scale = pixel_data->pixels[i].r;
                                p.y           = (scale * 2.0f - 1.0f) * m_terrain->m_height_map_scale;
                                m_terrain->m_grid.vertices[i].SetPosition(p);
                            }
                        }

                        m_terrain->CalculateNTB();
                        m_terrain->BuildBuffer();
                    }
                }
            }
        }
    }

    void TerrainComponent::Subscribe()
    {
        if (m_space != nullptr)
        {
            if (m_terrain != nullptr)
            {
                m_space->GetScene()->AddTerrain(m_terrain);
            }
        }
    }

    void TerrainComponent::Unsubscribe()
    {
        if (m_space != nullptr)
        {
            if (m_terrain != nullptr)
            {
                m_space->GetScene()->RemoveTerrain(m_terrain);
            }
        }
    }

    TerrainComponent::TerrainComponent(Object* owner)
        : Component(owner), m_edit_width(0), m_edit_depth(0), m_edit_w_lod(0), m_edit_d_lod(0), m_height_map_idx(0)
    {
    }

    void TerrainComponent::Clone(TerrainComponent* origin)
    {
    }
}
