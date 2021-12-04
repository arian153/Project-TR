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
#include "../../Input/KeyCode.hpp"

namespace GAM400
{
    class MouseInputWin32
    {
    public:
        MouseInputWin32();
        ~MouseInputWin32();

    protected:
        eKeyCodeMouse TranslateMessage(WPARAM wparam);
        int           TranslateMessage(eKeyCodeMouse button_code);
        
    private:
        friend class OSWin32;
    };
}
