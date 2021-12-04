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
#include "../OS-API/OSAPI.hpp"
#include IncludeKeyboardAPI
#include "KeyCode.hpp"
#include <string>

namespace GAM400
{
    class KeyboardInput : public KeyboardInputAPI
    {
    public:
        KeyboardInput();
        ~KeyboardInput();

    public: //interface 
        bool IsDown(eKeyCodeKeyboard key_code) const;
        bool IsPressed(eKeyCodeKeyboard key_code) const;
        bool IsAnyKeyDown() const;
        bool IsAnyKeyPressed() const;

        size_t        Repeated(eKeyCodeKeyboard key_code) const;
        std::string   TypedString() const;
        std::wstring* TypedWString() const;
        void          SetEditingWString(std::wstring* string);

    private:
        const static size_t MAXIMUM_KEY_COUNT = (size_t)eKeyCodeKeyboard::MAX;

        void Reset();
        void ResetPressed();
        void ProcessPressed();

    private:
        friend class InputCommon;

    private:
        ButtonState m_keyboard[ MAXIMUM_KEY_COUNT ];
    };
}
