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
#include "../../../System/Math/Utility/VectorDef.hpp"

namespace GAM400
{
    class TextureCommon;

    class SkyComponent final : public Component
    {
    public:
        ~SkyComponent();
        SkyComponent()                                   = delete;
        SkyComponent(const SkyComponent& rhs)            = delete;
        SkyComponent& operator=(const SkyComponent& rhs) = delete;

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
        friend class SkyFactory;
        friend class CubeMapSky;
        friend class TextureSky;

    private:
        explicit SkyComponent(Object* owner);
        void     Clone(SkyComponent* origin);

        void SwitchSkyType();

    private:
        CubeMapSky* m_cube_map_sky = nullptr;
        TextureSky* m_texture_sky  = nullptr;

        int            m_sky_type    = -1;
        TextureCommon* m_sky_texture = nullptr;
    };
}
