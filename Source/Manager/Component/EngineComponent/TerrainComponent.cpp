#include "TerrainComponent.hpp"

#include "TransformComponent.hpp"
#include "../../../External/JSONCPP/json/json.h"
#include "../../../System/Core/Utility/CoreUtility.hpp"
#include "../../../System/Graphics/Element/Scene.hpp"
#include "../../../System/Graphics/Element/Terrain.hpp"
#include "../../Object/Object.hpp"
#include "../../Resource/ResourceManager.hpp"
#include "../../Resource/ResourceType/JsonResource.hpp"
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
            m_terrain->ClearGrid();
            m_terrain->GenerateTrigonometric();
            m_terrain->BuildBuffer();
            m_terrain->m_component = this;
        }
    }

    void TerrainComponent::Update(Real dt)
    {
        Matrix44 world = Matrix44::Identity();
        if (m_owner->HasComponent<TransformComponent>())
        {
            world = m_owner->GetComponent<TransformComponent>()->GetTransformMatrix();
        }

        m_terrain->SetWorldMatrix(world);
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

        return true;
    }

    void TerrainComponent::Save(Json::Value& data) const
    {
    }

    void TerrainComponent::Edit(CommandRegistry* command_registry)
    {
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
        : Component(owner)
    {
    }

    void TerrainComponent::Clone(TerrainComponent* origin)
    {
    }
}
