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
#include "../../../System/Core/Core.hpp"
#include "../../../System/Math/Math.hpp"
#include "../../../Manager/Component/GameComponent/LogicComponent.hpp"
#include "../../../System/Math/Curve/Curve.hpp"

namespace Game
{
    class ControllerComponent final : public GAM400::LogicComponent
    {
    public:
        ~ControllerComponent();
        ControllerComponent()                                          = delete;
        ControllerComponent(const ControllerComponent& rhs)            = delete;
        ControllerComponent& operator=(const ControllerComponent& rhs) = delete;

        void Initialize() override;
        void Update(GAM400::Real dt) override;
        void Shutdown() override;
        void Render() override;

    protected:
        bool Load(const Json::Value& data) override;
        void Save(Json::Value& data) const override;
        void Edit(GAM400::CommandRegistry* command_registry) override;
        void Subscribe() override;
        void Unsubscribe() override;

    private:
        friend class ControllerFactory;

    private:
        explicit ControllerComponent(GAM400::Object* owner);
        void     Clone(ControllerComponent* origin);

    private:
        GAM400::Real    m_theta  = GAM400::Math::HALF_PI;
        GAM400::Real    m_phi    = GAM400::Math::HALF_PI;
        GAM400::Real    m_radius = 60.0f;
        GAM400::Vector3 target_pos;
        GAM400::Vector3 eye_pos;
    };
}
