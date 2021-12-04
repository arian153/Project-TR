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
#include IncludeRendererAPI

namespace GAM400
{
    class MeshBufferCommon;
    class ColorShaderCommon;

    class RendererCommon : public RendererAPI
    {
    public:
        RendererCommon();
        ~RendererCommon();

        void Initialize(int client_width, int client_height, bool b_fullscreen);
        void Shutdown();
        void OnResize(int client_width, int client_height, bool b_fullscreen);
        void OnFullscreen(bool b_fullscreen) const;
        void BeginScene(Color color) const;
        void EndScene() const;

        //setter
        void SetVSync(bool flag);
        void SetAlphaBlending(bool flag) const;
        void SetZBuffering(bool flag) const;
        bool IsInit() const;
    private:
        bool m_b_init = false;
    };
}
