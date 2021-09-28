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
