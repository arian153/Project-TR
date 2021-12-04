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
    class EditorCommand;

    class CommandRegistry
    {
    public:
        CommandRegistry();
        ~CommandRegistry();

        void Initialize();
        void Shutdown();

        void PushCommand(EditorCommand* command);
        void UndoCommand();
        void RedoCommand();
        void CopyCommand(void* data);
        void ClearUndoCommands();
        void Clear();

    private:
        friend class GameEditor;
    private:
        std::vector<EditorCommand*> m_command_registry;
        std::vector<EditorCommand*> m_undo_registry;

        //data
        void*  m_copied        = nullptr;
        size_t m_registry_size = 40;
    };
}
