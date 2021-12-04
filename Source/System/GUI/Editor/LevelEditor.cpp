/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/
#include "LevelEditor.hpp"

namespace GAM400
{
    LevelEditor::LevelEditor()
    {
    }

    LevelEditor::~LevelEditor()
    {
    }

    bool LevelEditor::Open(Level* level)
    {
        if (level != nullptr)
        {
            m_editing_level = level;
            return true;
        }
        return false;
    }

    void LevelEditor::Close()
    {
        m_editing_level = nullptr;
    }

    void LevelEditor::Update(Real dt)
    {
        if (m_b_open)
        {
            ImGui::Begin("Level Editor", &m_b_open);
            ImGui::Text("Level Editor");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }
    }
}
