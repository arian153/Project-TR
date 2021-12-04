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
#include "../Component.hpp"
#include "../../../System/Graphics/DataType/Color.hpp"

namespace GAM400
{
    class Transform;

    class ParticleEmitterComponent final : public Component
    {
    public:
        ~ParticleEmitterComponent();
        ParticleEmitterComponent()                                               = delete;
        ParticleEmitterComponent(const ParticleEmitterComponent& rhs)            = delete;
        ParticleEmitterComponent& operator=(const ParticleEmitterComponent& rhs) = delete;

        void Initialize() override;
        void Update(Real dt) override;
        void Shutdown() override;

    protected:
        bool Load(const Json::Value& data) override;
        void Save(Json::Value& data) const override;
        void Edit(CommandRegistry* command_registry) override;
        void Subscribe() override;
        void Unsubscribe() override;

    private:
        friend class ParticleEmitterFactory;
        friend class ParticleEmitter;

    private:
        explicit ParticleEmitterComponent(Object* owner);
        void     Clone(ParticleEmitterComponent* origin);

    private:
        ParticleEmitter* m_emitter   = nullptr;
        Transform*       m_transform = nullptr;

        size_t m_edit_slider_particle_amount = 0;
        size_t m_edit_slider_emission_amount = 0;
        Color  m_edit_color_base;
        Color  m_edit_color_variance;
    };
}
