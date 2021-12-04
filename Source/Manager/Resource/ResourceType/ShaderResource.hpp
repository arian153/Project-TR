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
#include "../Resource.hpp"

namespace GAM400
{
    enum class eShaderStage : int
    {
        IntegratedShader = -1,
        VertexShader,
        PixelShader,
        InvalidShader
    };

    class ShaderResource final : public Resource
    {
    public:
        explicit ShaderResource(const std::wstring& path);
        ~ShaderResource();

        void Initialize() override;
        void Shutdown() override;

        void SetStage(eShaderStage stage);

    private:
        bool         m_b_integrated_shader = false;
        eShaderStage m_stage;
    };
}
