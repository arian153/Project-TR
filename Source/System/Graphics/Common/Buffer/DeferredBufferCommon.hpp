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
#include "../../../Core/Utility/CoreDef.hpp"
#include "../../GraphicsAPI.hpp"
#include IncludeDeferredBufferAPI

namespace GAM400
{
    class RendererCommon;
    class Color;

    class DeferredBufferCommon : public DeferredBufferAPI
    {
    public:
        DeferredBufferCommon();
        ~DeferredBufferCommon();

        bool Initialize(RendererCommon* renderer, U32 texture_width, U32 texture_height);
        void Render() const;
        void Shutdown();

        bool OnResize(U32 texture_width, U32 texture_height);

        void SetRenderTargets() const;
        void ClearRenderTargets(const Color& color);
    private:
    };

    
}
