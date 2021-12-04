/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include "LogicSystem.hpp"
#include "LogicSubsystem.hpp"

namespace GAM400
{
    LogicSystem::LogicSystem()
    {
    }

    LogicSystem::~LogicSystem()
    {
    }

    void LogicSystem::Initialize()
    {
    }

    void LogicSystem::Shutdown()
    {
        for (auto& logic : m_subsystems)
        {
            logic->Shutdown();
            delete logic;
            logic = nullptr;
        }
        m_subsystems.clear();
    }

    void LogicSystem::SetInput(InputCommon* input)
    {
        m_input = input;
    }

    void LogicSystem::SetTextRenderer(TextRenderer* text_renderer)
    {
        m_text_renderer = text_renderer;
    }

    LogicSubsystem* LogicSystem::CreateLogicSubsystem()
    {
        LogicSubsystem* logic  = new LogicSubsystem();
        logic->m_input         = m_input;
        logic->m_text_renderer = m_text_renderer;
        m_subsystems.push_back(logic);
        return logic;
    }

    void LogicSystem::RemoveLogicSubsystem(LogicSubsystem* logic_subsystem)
    {
        if (logic_subsystem != nullptr)
        {
            auto found = std::find(m_subsystems.begin(), m_subsystems.end(), logic_subsystem);
            m_subsystems.erase(found);
            logic_subsystem->Shutdown();
            delete logic_subsystem;
            logic_subsystem = nullptr;
        }
    }
}
