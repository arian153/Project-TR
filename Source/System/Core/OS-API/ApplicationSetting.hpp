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
#include "WindowMode.hpp"
#include "../../Math/Utility/MathDef.hpp"
#include <string>

namespace GAM400
{
    struct ApplicationSetting
    {
    public:
        bool b_confine_cursor = false;
        bool b_show_cursor    = true;
        bool b_v_sync         = true;

        int  screen_width  = 1280;
        int  screen_height = 720;
        Real screen_scale  = 1.0f;

        std::string caption       = "";
        std::string initial_level = "";
        std::string edit_space    = "";
        eWindowMode window_mode   = eWindowMode::Windowed;
    };
}
