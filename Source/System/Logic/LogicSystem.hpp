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
#include <vector>

namespace GAM400
{
    class TextRenderer;
    class InputCommon;
    class LogicSubsystem;

    class LogicSystem
    {
    public:
        LogicSystem();
        ~LogicSystem();

        void Initialize();
        void Shutdown();

        void SetInput(InputCommon* input);
        void SetTextRenderer(TextRenderer* text_renderer);

        LogicSubsystem* CreateLogicSubsystem();
        void            RemoveLogicSubsystem(LogicSubsystem* logic_subsystem);

    private:
        std::vector<LogicSubsystem*> m_subsystems;

        //others
        InputCommon*  m_input         = nullptr;
        TextRenderer* m_text_renderer = nullptr;
    };
}
