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

#if defined(GAM400_WIN32)
//classes
#define OSAPI OSWin32
#define KeyboardInputAPI KeyboardInputWin32
#define MouseInputAPI MouseInputWin32
#define GamePadInputAPI GamePadInputWin32
//includes
#define IncludeOSAPI "Win32/OSWin32.hpp"
#define IncludeKeyboardAPI "../OS-API/Win32/KeyboardInputWin32.hpp"
#define IncludeMouseAPI "../OS-API/Win32/MouseInputWin32.hpp"
#define IncludeGamePadAPI "../OS-API/Win32/GamePadInputWin32.hpp"

#endif
