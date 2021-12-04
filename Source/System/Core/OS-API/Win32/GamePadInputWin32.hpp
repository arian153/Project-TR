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
#include <windows.h>
#include <Xinput.h>

namespace GAM400
{
    struct PadState;
    class GamePadInputWin32
    {
    public:
        GamePadInputWin32();
        ~GamePadInputWin32();

    protected:
        void ProcessButtons(XINPUT_GAMEPAD* game_pad, PadState& pad_state) const;
        void ProcessLeftThumb(XINPUT_GAMEPAD* game_pad, PadState& pad_state) const;
        void ProcessRightThumb(XINPUT_GAMEPAD* game_pad, PadState& pad_state) const;
        void ProcessTrigger(XINPUT_GAMEPAD* game_pad, PadState& pad_state) const;

    protected:
        const static size_t USER_MAX_COUNT = XUSER_MAX_COUNT;
        XINPUT_STATE        m_controllers[USER_MAX_COUNT];
    };
}
