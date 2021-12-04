/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include "EditorCommand.hpp"

namespace GAM400
{
    EditorCommand::EditorCommand()
    {
    }

    EditorCommand::~EditorCommand()
    {
    }

    void EditorCommand::SetRegistry(CommandRegistry* registry)
    {
        m_registry = registry;
    }

    std::string EditorCommand::Type() const
    {
        return m_type;
    }

    const char* EditorCommand::TypeCStr() const
    {
        return m_type.c_str();
    }
}
