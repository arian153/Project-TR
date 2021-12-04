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
#include IncludeTextTextureBufferAPI

namespace GAM400
{
    class RendererCommon;
    class Color;

    class TextTextureBufferCommon : public TextTextureBufferAPI
    {
    public:
        TextTextureBufferCommon();
        ~TextTextureBufferCommon();

        bool Initialize(RendererCommon* renderer);
        bool Update();
        void Render();
        void Shutdown();

        void SetText(const std::string& string) const;
        void SetText(const std::wstring& string) const;
        void SetFont(const std::wstring& font) const;
        void SetColor(Color color);

        U32   GetIndexCount() const;
        U32   GetVertexCount() const;
        Color GetColor() const;

    private:
    };
}
