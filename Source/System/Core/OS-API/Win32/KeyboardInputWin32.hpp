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
#include <string>
#include <windows.h>
#include "../../Input/KeyCode.hpp"

namespace GAM400
{
    class KeyboardInputWin32
    {
    public:
        KeyboardInputWin32();
        ~KeyboardInputWin32();

    protected:
        void             ProcessString(WPARAM wparam) const;
        eKeyCodeKeyboard TranslateMessage(WPARAM wparam);
        int              TranslateMessage(eKeyCodeKeyboard key_code);
    private:
        friend class OSWin32;
    protected:
        std::wstring* m_string = nullptr;
    };
}
