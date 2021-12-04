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
#include <dwrite_2.h>
#include <d2d1_2.h>
#include <string>
#include "../../../Math/Utility/MathDef.hpp"

namespace GAM400
{
    class TextFormatBufferDX11
    {
    public:
        TextFormatBufferDX11();
        ~TextFormatBufferDX11();

        bool BuildTextFormats(const std::wstring& font, Real font_size);

        IDWriteTextFormat* GetTextFormat() const;

    protected:
        IDWriteFactory2* m_write_factory = nullptr;
        IDWriteTextFormat* m_text_format = nullptr;
    };
}
