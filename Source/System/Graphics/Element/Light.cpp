/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include "Light.hpp"

#include "../../../Manager/Component/EngineComponent/LightComponent.hpp"

namespace GAM400
{
    Light::Light()
        : light_data()
    {
    }

    Light::~Light()
    {
    }

    void Light::Initialize()
    {
    }

    void Light::Update(Real dt) const
    {
        if (m_component != nullptr)
        {
            m_component->Update(dt);
        }
    }

    void Light::Shutdown() const
    {
        if (m_component != nullptr)
        {
            m_component->m_light = nullptr;
        }
    }

    LightBufferData Light::GetLightBuffer() const
    {
        return light_data;
    }

    void Light::SetType(const eLightType& type)
    {
        m_type          = type;
        light_data.type = (int)type;
    }

    void Light::SetAmbientColor(const Color& color)
    {
        light_data.ambient_color = color;
    }

    void Light::SetDiffuseColor(const Color& color)
    {
        light_data.diffuse_color = color;
    }

    void Light::SetSpecularColor(const Color& color)
    {
        light_data.specular_color = color;
    }

    void Light::SetAmbientRange(const Color& color)
    {
        light_data.ambient_range = color;
    }

    void Light::SetLightDirection(const Vector3& direction)
    {
        light_data.direction = direction;
    }

    void Light::SetLightRange(const Real& range)
    {
        light_data.range = range;
    }

    void Light::SetLightPosition(const Vector3& position)
    {
        light_data.position = position;
    }

    void Light::SetLightLength(const Real& length)
    {
        light_data.length = length;
    }

    void Light::SetAttenuation(const Vector3& att)
    {
        light_data.attenuation = att;
    }

    void Light::SetSpot(const Real& spot)
    {
        light_data.spot = spot;
    }

    void Light::SetIntensity(const Real& intensity)
    {
        light_data.intensity = intensity;
    }
}
