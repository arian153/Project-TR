/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include "InputCommon.hpp"
#include "MouseInput.hpp"
#include "GamePadInput.hpp"
#include "KeyboardInput.hpp"

namespace GAM400
{
    InputCommon::InputCommon()
    {
    }

    InputCommon::~InputCommon()
    {
    }

    void InputCommon::Initialize()
    {
        m_mouse_input    = new MouseInput();
        m_keyboard_input = new KeyboardInput();
        m_game_pad_input = new GamePadInput();
    }

    void InputCommon::Update() const
    {
        m_game_pad_input->ProcessGamePad();
        m_game_pad_input->ProcessPressed();
        m_keyboard_input->ProcessPressed();
        m_mouse_input->ProcessPressed();
    }

    void InputCommon::Shutdown()
    {
        if (m_mouse_input != nullptr)
        {
            delete m_mouse_input;
            m_mouse_input = nullptr;
        }
        if (m_keyboard_input != nullptr)
        {
            delete m_keyboard_input;
            m_keyboard_input = nullptr;
        }
        if (m_game_pad_input != nullptr)
        {
            delete m_game_pad_input;
            m_game_pad_input = nullptr;
        }
    }

    MouseInput* InputCommon::GetMouseInput() const
    {
        return m_mouse_input;
    }

    KeyboardInput* InputCommon::GetKeyboardInput() const
    {
        return m_keyboard_input;
    }

    GamePadInput* InputCommon::GetGamePadInput() const
    {
        return m_game_pad_input;
    }
}
