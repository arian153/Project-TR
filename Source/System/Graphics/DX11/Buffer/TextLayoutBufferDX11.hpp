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

#include "../../../Core/Utility/CoreDef.hpp"
#include "../../../Math/Algebra/Vector2.hpp"

namespace GAM400
{
    class TextFormatBufferCommon;

    class TextLayoutBufferDX11
    {
    public:
        TextLayoutBufferDX11();
        ~TextLayoutBufferDX11();

        bool SetTextLayout(const std::wstring& text, U32 width, U32 height);
        void SetTextFormat(TextFormatBufferCommon* text_format);

    protected:
        IDWriteFactory2*      m_write_factory      = nullptr;
        ID2D1DeviceContext1*  m_d2d_device_context = nullptr;
        IDWriteTextFormat*    m_text_format        = nullptr;
        IDWriteTextLayout*    m_text_layout        = nullptr;
        ID2D1SolidColorBrush* m_brush              = nullptr;
        Vector2               m_position;
    };
}
