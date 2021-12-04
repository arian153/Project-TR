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

namespace GAM400
{
    class MouseInput;
    class KeyboardInput;
    class GamePadInput;

    class InputCommon
    {
    public:
        InputCommon();
        ~InputCommon();

        void Initialize();
        void Update() const;
        void Shutdown();

        MouseInput*    GetMouseInput() const;
        KeyboardInput* GetKeyboardInput() const;
        GamePadInput*  GetGamePadInput() const;
    private:
        MouseInput*    m_mouse_input    = nullptr;
        KeyboardInput* m_keyboard_input = nullptr;
        GamePadInput*  m_game_pad_input = nullptr;
    };
}
