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

#include "../../GraphicsAPI.hpp"
#include IncludeShaderProgramAPI

#include "../../../Math/Utility/MathDef.hpp"
#include "../../../Core/Utility/CoreDef.hpp"

namespace GAM400
{
    class ConstantBufferCommon;
    class ShaderResource;
    class ShaderManagerCommon;
    class RendererCommon;
    class VertexLayoutCommon;

    class ShaderProgramCommon : public ShaderProgramAPI
    {
    public:
        explicit ShaderProgramCommon(ShaderManagerCommon* shader_manager);
        ~ShaderProgramCommon();

        bool Init(RendererCommon* renderer);
        void Shutdown();
        void Bind() const;

        void SetVertexLayout(VertexLayoutCommon* layout);
        void SetShaderResource(ShaderResource* resource);

    private:
        ShaderManagerCommon* m_shader_manager = nullptr;
        ShaderResource*      m_resource       = nullptr;
        VertexLayoutCommon*  m_vertex_layout  = nullptr;

        std::vector<ConstantBufferCommon*> m_constant_buffers;
    };
}
