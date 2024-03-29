/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#pragma once
#include "..//Component.hpp"
#include "../../../System/Graphics/Common/Buffer2/ConstantBufferData.hpp"
#include "../../../System/Graphics/Element/LightDef.hpp"
#include "../../../System/Math/Utility/VectorDef.hpp"

namespace GAM400
{
    class Light;
    class Quaternion;
    class Vector3;
    class Transform;

    class LightComponent final : public Component
    {
    public:
        ~LightComponent();
        LightComponent()                                     = delete;
        LightComponent(const LightComponent& rhs)            = delete;
        LightComponent& operator=(const LightComponent& rhs) = delete;

        void Initialize() override;
        void Update(Real dt) override;
        void Shutdown() override;

        void SetLightType(eLightType type);
        void SetLightDirection(const Vector3& dir) const;

        Light* GetLight() const;

    protected:
        bool Load(const Json::Value& data) override;
        void Save(Json::Value& data) const override;
        void Edit(CommandRegistry* command_registry) override;
        void Subscribe() override;
        void Unsubscribe() override;

    private:
        friend class LightFactory;
        friend class Light;

    private:
        explicit LightComponent(Object* owner);
        void     Clone(LightComponent* origin);

    private:
        Light*    m_light      = nullptr;
        Transform* m_transform  = nullptr;
        eLightType m_light_type = eLightType::DirectionalLight;

        LightBufferData edit_data;
    };
}
