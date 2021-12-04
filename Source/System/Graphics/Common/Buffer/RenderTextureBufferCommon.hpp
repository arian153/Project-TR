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
#include IncludeRenderTextureBufferAPI
#include "../../../Math/Utility/MathDef.hpp"

namespace GAM400
{
    class RendererCommon;

    class RenderTextureBufferCommon : public RenderTextureBufferAPI
    {
    public:
        RenderTextureBufferCommon();
        ~RenderTextureBufferCommon();

        bool Initialize(RendererCommon* renderer, size_t width, size_t height);
        void Render() const;
        void Shutdown();
        bool OnResize(size_t width, size_t height) ;
        U32  GetIndexCount() const;
    private:
    };
}
