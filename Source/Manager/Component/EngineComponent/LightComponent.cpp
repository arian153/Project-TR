/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include "LightComponent.hpp"
#include "../../../System/Core/Utility/CoreUtility.hpp"
#include "../../Resource/ResourceType/JsonResource.hpp"
#include "../../../External/JSONCPP/json/json.h"
#include "../../Space/Space.hpp"
#include "../../../System/Graphics/Element/Scene.hpp"
#include "TransformComponent.hpp"
#include "../../../System/Graphics/Element/Light.hpp"
#include "../../../System/GUI/Editor/Command/CommandRegistry.hpp"
#include "../../../System/GUI/Editor/Command/EditorCommand.hpp"
#include "../../Object/Object.hpp"

namespace GAM400
{
    LightComponent::~LightComponent()
    {
    }

    void LightComponent::Initialize()
    {
        if (m_light == nullptr)
        {
            m_light = new Light();
            m_light->Initialize();
            m_light->m_component = this;
            Subscribe();
        }

        if (m_transform == nullptr)
        {
            if (m_owner->HasComponent<TransformComponent>())
            {
                m_transform = m_owner->GetComponent<TransformComponent>()->GetTransform();
            }
        }
    }

    void LightComponent::Update(Real dt)
    {
        E5_UNUSED_PARAM(dt);

        if (m_transform != nullptr)
        {
            m_light->light_data.position = m_transform->position;
        }

        if (m_owner->HasComponent<MeshComponent>())
        {
            auto mesh = m_owner->GetComponent<MeshComponent>();
            if (m_light_type == eLightType::AmbientLight)
            {
                mesh->SetDiffuseColor(m_light->light_data.ambient_range);
            }
            else
            {
                mesh->SetDiffuseColor(m_light->light_data.diffuse_color);
            }
        }
    }

    void LightComponent::Shutdown()
    {
        Unsubscribe();
        if (m_light != nullptr)
        {
            m_light->Shutdown();
            delete m_light;
            m_light = nullptr;
        }
    }

    void LightComponent::SetLightType(eLightType type)
    {
        m_light_type = type;
        m_light->SetType(type);
    }

    void LightComponent::SetLightDirection(const Vector3& dir) const
    {
        m_light->light_data.direction = dir;
    }

    Light* LightComponent::GetLight() const
    {
        return m_light;
    }

    bool LightComponent::Load(const Json::Value& data)
    {
        if (JsonResource::HasMember(data, "Type"))
        {
            if (data["Type"].isString())
            {
                std::string light_type = data["Type"].asString();

                if (light_type == "AmbientLight")
                {
                    SetLightType(eLightType::AmbientLight);
                }
                else if (light_type == "DirectionalLight")
                {
                    SetLightType(eLightType::DirectionalLight);
                }
                else if (light_type == "PointLight")
                {
                    SetLightType(eLightType::PointLight);
                }
                else if (light_type == "SpotLight")
                {
                    SetLightType(eLightType::SpotLight);
                }
                else if (light_type == "CapsuleLight")
                {
                    SetLightType(eLightType::CapsuleLight);
                }
            }

            if (data["Type"].isInt())
            {
                int light_type = data["Type"].asInt();
                light_type %= 5;

                SetLightType((eLightType)light_type);
            }
        }
        if (JsonResource::HasMember(data, "Ambient Color") && JsonResource::IsColor(data["Ambient Color"]))
        {
            m_light->light_data.ambient_color = JsonResource::AsColor(data["Ambient Color"]);
        }
        if (JsonResource::HasMember(data, "Ambient Range") && JsonResource::IsColor(data["Ambient Range"]))
        {
            m_light->light_data.ambient_range = JsonResource::AsColor(data["Ambient Range"]);
        }
        if (JsonResource::HasMember(data, "Diffuse Color") && JsonResource::IsColor(data["Diffuse Color"]))
        {
            m_light->light_data.diffuse_color = JsonResource::AsColor(data["Diffuse Color"]);
        }
        if (JsonResource::HasMember(data, "Specular Color") && JsonResource::IsColor(data["Specular Color"]))
        {
            m_light->light_data.specular_color = (JsonResource::AsColor(data["Specular Color"]));
        }
        if (JsonResource::HasMember(data, "Intensity") && data["Intensity"].isDouble())
        {
            m_light->light_data.intensity = (data["Intensity"].asFloat());
        }

        if (JsonResource::HasMember(data, "Direction") && JsonResource::IsVector3(data["Direction"]))
        {
            m_light->light_data.direction = (JsonResource::AsVector3(data["Direction"]));
            m_light->light_data.direction.SetNormalize();
        }
        if (JsonResource::HasMember(data, "Position") && JsonResource::IsVector3(data["Position"]))
        {
            m_light->light_data.position = (JsonResource::AsVector3(data["Position"]));
        }
        if (JsonResource::HasMember(data, "Attenuation") && JsonResource::IsVector3(data["Attenuation"]))
        {
            m_light->light_data.attenuation = (JsonResource::AsVector3(data["Attenuation"]));
        }
        if (JsonResource::HasMember(data, "Length") && data["Length"].isDouble())
        {
            m_light->light_data.length = (data["Length"].asFloat());
        }
        if (JsonResource::HasMember(data, "Range") && data["Range"].isDouble())
        {
            m_light->light_data.range = (data["Range"].asFloat());
        }
        if (JsonResource::HasMember(data, "Spot") && data["Spot"].isDouble())
        {
            m_light->light_data.spot = (data["Spot"].asFloat());
        }
        return true;
    }

    void LightComponent::Save(Json::Value& data) const
    {
    }

    void LightComponent::Edit(CommandRegistry* command_registry)
    {
        if (ImGui::CollapsingHeader(m_type.c_str(), &m_b_open))
        {
            ImGui::Text("Light Type");
            const char* light_type[] = {"Ambient Light", "Directional Light", "Point Light", "Spot Light", "Capsule Light"};

            if (ImGui::Combo("##Light Type", (int*)&m_light_type, light_type, 5))
            {
                eLightType  prev    = m_light->m_type;
                eLightType  next    = m_light_type;
                std::string message = "Change Light Type : " + std::string(light_type[(int)prev]) + " To " + std::string(light_type[(int)next]);
                command_registry->PushCommand(
                                              new EditFunction<
                                                  eLightType,
                                                  Light,
                                                  &Light::SetType>(m_light, prev, next, message));
            }

            ImGui::Text("Ambient Color");

            Color color = m_light->light_data.ambient_color;
            ImGui::ColorEdit4("##Ambient Color", &m_light->light_data.ambient_color.r);
            if (ImGui::IsItemActivated())
            {
                edit_data.ambient_color = color;
            }
            if (ImGui::IsItemDeactivatedAfterEdit())
            {
                std::string message = "Change Ambient Color";
                command_registry->PushCommand(
                                              new EditFunction<
                                                  Color,
                                                  Light,
                                                  &Light::SetAmbientColor>(m_light, edit_data.ambient_color, m_light->light_data.ambient_color, message));
            }

            if (m_light_type == eLightType::AmbientLight)
            {
                ImGui::Text("Ambient Range");
                color = m_light->light_data.ambient_range;
                ImGui::ColorEdit4("##Ambient Range", &m_light->light_data.ambient_range.r);
                if (ImGui::IsItemActivated())
                {
                    edit_data.ambient_range = color;
                }
                if (ImGui::IsItemDeactivatedAfterEdit())
                {
                    std::string message = "Change Ambient Range";
                    command_registry->PushCommand(
                                                  new EditFunction<
                                                      Color,
                                                      Light,
                                                      &Light::SetAmbientRange>(m_light, edit_data.ambient_range, m_light->light_data.ambient_range, message));
                }
            }
            else
            {
                ImGui::Text("Diffuse Color");
                color = m_light->light_data.diffuse_color;
                if (ImGui::ColorEdit4("##Diffuse Color", &m_light->light_data.diffuse_color.r))
                {
                }
                if (ImGui::IsItemActivated())
                {
                    edit_data.diffuse_color = color;
                }
                if (ImGui::IsItemDeactivatedAfterEdit())
                {
                    std::string message = "Change Diffuse Color";
                    command_registry->PushCommand(
                                                  new EditFunction<
                                                      Color,
                                                      Light,
                                                      &Light::SetDiffuseColor>(m_light, edit_data.diffuse_color, m_light->light_data.diffuse_color, message));
                }

                ImGui::Text("Specular Color");
                color = m_light->light_data.specular_color;
                ImGui::ColorEdit4("##Specular Color", &m_light->light_data.specular_color.r);
                if (ImGui::IsItemActivated())
                {
                    edit_data.specular_color = color;
                }
                if (ImGui::IsItemDeactivatedAfterEdit())
                {
                    std::string message = "Change Specular Color";
                    command_registry->PushCommand(
                                                  new EditFunction<
                                                      Color,
                                                      Light,
                                                      &Light::SetSpecularColor>(m_light, edit_data.specular_color, m_light->light_data.specular_color, message));
                }

                ImGui::Text("Intensity");
                Real    vector1 = m_light->light_data.intensity;
                Vector3 vector3;
                ImGui::DragFloat("##Intensity", &m_light->light_data.intensity);
                if (ImGui::IsItemActivated())
                {
                    edit_data.intensity = vector1;
                }
                if (ImGui::IsItemDeactivatedAfterEdit())
                {
                    std::string message = "Change Light Intensity";
                    command_registry->PushCommand(
                                                  new EditFunction<
                                                      Real,
                                                      Light,
                                                      &Light::SetIntensity>(m_light, edit_data.intensity, m_light->light_data.intensity, message));
                }

                if (m_light_type == eLightType::DirectionalLight)
                {
                    ImGui::Text("Direction");
                    vector3 = m_light->light_data.direction;
                    ImGui::InputFloat3("##Direction", &m_light->light_data.direction.x);
                    if (ImGui::IsItemActivated())
                    {
                        edit_data.direction = vector3;
                    }
                    if (ImGui::IsItemDeactivatedAfterEdit())
                    {
                        std::string message = "Change Light Direction";
                        command_registry->PushCommand(
                                                      new EditFunction<
                                                          Vector3,
                                                          Light,
                                                          &Light::SetLightDirection>(m_light, edit_data.direction, m_light->light_data.direction, message));
                    }
                }
                else if (m_light_type == eLightType::PointLight)
                {
                    Vector3 pos = m_light->light_data.position;
                    ImGui::Text("Position");
                    ImGui::Text("[%.3f, %.3f, %.3f]", pos[0], pos[1], pos[2]);
                    ImGui::Text("Range");
                    vector1 = m_light->light_data.range;
                    ImGui::InputFloat("##Range", &m_light->light_data.range);
                    if (ImGui::IsItemActivated())
                    {
                        edit_data.range = vector1;
                    }
                    if (ImGui::IsItemDeactivatedAfterEdit())
                    {
                        std::string message = "Change Light Range";
                        command_registry->PushCommand(
                                                      new EditFunction<
                                                          Real,
                                                          Light,
                                                          &Light::SetLightRange>(m_light, edit_data.range, m_light->light_data.range, message));
                    }
                    ImGui::Text("Attenuation");
                    vector3 = m_light->light_data.attenuation;
                    ImGui::InputFloat3("##Attenuation", &m_light->light_data.attenuation.x);
                    if (ImGui::IsItemActivated())
                    {
                        edit_data.attenuation = vector3;
                    }
                    if (ImGui::IsItemDeactivatedAfterEdit())
                    {
                        std::string message = "Change Light Attenuation";
                        command_registry->PushCommand(
                                                      new EditFunction<
                                                          Vector3,
                                                          Light,
                                                          &Light::SetAttenuation>(m_light, edit_data.attenuation, m_light->light_data.attenuation, message));
                    }
                }
                else if (m_light_type == eLightType::SpotLight)
                {
                    Vector3 pos = m_light->light_data.position;
                    ImGui::Text("Position");
                    ImGui::Text("[%.3f, %.3f, %.3f]", pos[0], pos[1], pos[2]);

                    ImGui::Text("Direction");
                    vector3 = m_light->light_data.direction;
                    ImGui::InputFloat3("##Direction", &m_light->light_data.direction.x);
                    if (ImGui::IsItemActivated())
                    {
                        edit_data.direction = vector3;
                    }
                    if (ImGui::IsItemDeactivatedAfterEdit())
                    {
                        std::string message = "Change Light Direction";
                        command_registry->PushCommand(
                                                      new EditFunction<
                                                          Vector3,
                                                          Light,
                                                          &Light::SetLightDirection>(m_light, edit_data.direction, m_light->light_data.direction, message));
                    }

                    ImGui::Text("Spot");
                    vector1 = m_light->light_data.spot;
                    ImGui::InputFloat("##Spot", &m_light->light_data.spot);
                    if (ImGui::IsItemActivated())
                    {
                        edit_data.spot = vector1;
                    }
                    if (ImGui::IsItemDeactivatedAfterEdit())
                    {
                        std::string message = "Change Spot";
                        command_registry->PushCommand(
                                                      new EditFunction<
                                                          Real,
                                                          Light,
                                                          &Light::SetSpot>(m_light, edit_data.spot, m_light->light_data.spot, message));
                    }

                    ImGui::Text("Range");
                    vector1 = m_light->light_data.range;
                    ImGui::InputFloat("##Range", &m_light->light_data.range);
                    if (ImGui::IsItemActivated())
                    {
                        edit_data.range = vector1;
                    }
                    if (ImGui::IsItemDeactivatedAfterEdit())
                    {
                        std::string message = "Change Light Range";
                        command_registry->PushCommand(
                                                      new EditFunction<
                                                          Real,
                                                          Light,
                                                          &Light::SetLightRange>(m_light, edit_data.range, m_light->light_data.range, message));
                    }

                    ImGui::Text("Attenuation");
                    vector3 = m_light->light_data.attenuation;
                    ImGui::InputFloat3("##Attenuation", &m_light->light_data.attenuation.x);
                    if (ImGui::IsItemActivated())
                    {
                        edit_data.attenuation = vector3;
                    }
                    if (ImGui::IsItemDeactivatedAfterEdit())
                    {
                        std::string message = "Change Light Attenuation";
                        command_registry->PushCommand(
                                                      new EditFunction<
                                                          Vector3,
                                                          Light,
                                                          &Light::SetAttenuation>(m_light, edit_data.attenuation, m_light->light_data.attenuation, message));
                    }
                }
                else if (m_light_type == eLightType::CapsuleLight)
                {
                    Vector3 pos = m_light->light_data.position;
                    ImGui::Text("Position");
                    ImGui::Text("[%.3f, %.3f, %.3f]", pos[0], pos[1], pos[2]);

                    ImGui::Text("Direction");
                    vector3 = m_light->light_data.direction;
                    ImGui::InputFloat3("##Direction", &m_light->light_data.direction.x);
                    if (ImGui::IsItemActivated())
                    {
                        edit_data.direction = vector3;
                    }
                    if (ImGui::IsItemDeactivatedAfterEdit())
                    {
                        std::string message = "Change Light Direction";
                        command_registry->PushCommand(
                                                      new EditFunction<
                                                          Vector3,
                                                          Light,
                                                          &Light::SetLightDirection>(m_light, edit_data.direction, m_light->light_data.direction, message));
                    }

                    ImGui::Text("Length");
                    vector1 = m_light->light_data.length;
                    ImGui::InputFloat("##Length", &m_light->light_data.length);
                    if (ImGui::IsItemActivated())
                    {
                        edit_data.length = vector1;
                    }
                    if (ImGui::IsItemDeactivatedAfterEdit())
                    {
                        std::string message = "Change Light Length";
                        command_registry->PushCommand(
                                                      new EditFunction<
                                                          Real,
                                                          Light,
                                                          &Light::SetLightLength>(m_light, edit_data.length, m_light->light_data.length, message));
                    }

                    ImGui::Text("Range");
                    vector1 = m_light->light_data.range;
                    ImGui::InputFloat("##Range", &m_light->light_data.range);
                    if (ImGui::IsItemActivated())
                    {
                        edit_data.range = vector1;
                    }
                    if (ImGui::IsItemDeactivatedAfterEdit())
                    {
                        std::string message = "Change Light Range";
                        command_registry->PushCommand(
                                                      new EditFunction<
                                                          Real,
                                                          Light,
                                                          &Light::SetLightRange>(m_light, edit_data.range, m_light->light_data.range, message));
                    }

                    ImGui::Text("Attenuation");
                    vector3 = m_light->light_data.attenuation;
                    ImGui::InputFloat3("##Attenuation", &m_light->light_data.attenuation.x);
                    if (ImGui::IsItemActivated())
                    {
                        edit_data.attenuation = vector3;
                    }
                    if (ImGui::IsItemDeactivatedAfterEdit())
                    {
                        std::string message = "Change Light Attenuation";
                        command_registry->PushCommand(
                                                      new EditFunction<
                                                          Vector3,
                                                          Light,
                                                          &Light::SetAttenuation>(m_light, edit_data.attenuation, m_light->light_data.attenuation, message));
                    }
                }
            }
        }
    }

    void LightComponent::Subscribe()
    {
        if (m_space != nullptr && m_light != nullptr)
        {
            m_space->GetScene()->AddLight(m_light);
        }
    }

    void LightComponent::Unsubscribe()
    {
        if (m_space != nullptr && m_light != nullptr)
        {
            m_space->GetScene()->RemoveLight(m_light);
        }
    }

    LightComponent::LightComponent(Object* owner)
        : Component(owner)
    {
    }

    void LightComponent::Clone(LightComponent* origin)
    {
    }
}
