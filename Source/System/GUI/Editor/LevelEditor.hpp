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
#include "../../../External/imgui/imgui.h"
#include "../../Math/Utility/MathDef.hpp"

namespace GAM400
{
    class Level;

    class LevelEditor
    {
    public:
        LevelEditor();
        ~LevelEditor();

        bool Open(Level* space);
        void Close();

        void Update(Real dt);

    private:
        friend class GameEditor;

    private:
        bool   m_b_open        = false;
        Level* m_editing_level = nullptr;
    };
}
