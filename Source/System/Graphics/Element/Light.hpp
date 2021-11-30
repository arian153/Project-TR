#pragma once
#include "LightDef.hpp"
#include "../../Math/Algebra/Vector3.hpp"
#include "../Common/Buffer2/ConstantBufferData.hpp"
#include "../DataType/Color.hpp"

namespace GAM400
{
    class LightComponent;

    class Light
    {
    public:
        Light();
        ~Light();

        void Initialize();
        void Update(Real dt) const;
        void Shutdown() const;

        LightBufferData GetLightBuffer() const;
        void            SetType(const eLightType& type);

        void SetAmbientColor(const Color& color);
        void SetDiffuseColor(const Color& color);
        void SetSpecularColor(const Color& color);
        void SetAmbientRange(const Color& color);

        void SetLightDirection(const Vector3& direction);
        void SetLightRange(const Real& range);
        void SetLightPosition(const Vector3& position);
        void SetLightLength(const Real& length);
        void SetAttenuation(const Vector3& att);
        void SetSpot(const Real& spot);
        void SetIntensity(const Real& intensity);

    public:
        LightBufferData light_data;

    private:
        friend class LightComponent;
    private:
        LightComponent* m_component = nullptr;
        eLightType      m_type      = eLightType::PointLight;
    };
}
