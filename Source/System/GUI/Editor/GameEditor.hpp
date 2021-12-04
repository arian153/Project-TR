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
#include "../../Math/Utility/MathDef.hpp"
#include "LevelEditor.hpp"
#include "SpaceEditor.hpp"
#include "../../../External/imgui/imgui.h"
#include "Command/CommandRegistry.hpp"

namespace GAM400
{
    class TextureResource;
    class KeyboardInput;
    class InputCommon;
    class ObjectFactory;
    class GUISystem;
    class Application;

    class GameEditor
    {
    public:
        GameEditor();
        ~GameEditor();

        void Initialize(Application* application);
        void Update(Real dt);
        void Shutdown();

        bool IsOpen() const;
        void SetOpen(bool is_open);

        CommandRegistry* GetCommandRegistry();

        void SetInitialEditSpace(const std::string& space);
    private:
        void UpdateFileTab();
        void UpdateEditTab();
        void UpdateObjectTab();
        void UpdateHelpTab();

        void UpdateCommandWindow();
        void ShowReadMe();
        void UpdateShortCuts();

        void ShowLicense();
        void ShowAbout();
        void ShowCredit();

    private:
        LevelEditor     m_level_editor;
        SpaceEditor     m_space_editor;
        Application*    m_application = nullptr;
        CommandRegistry m_command_registry;

        ObjectFactory*   m_object_factory   = nullptr;
        ResourceManager* m_resource_manager = nullptr;
        InputCommon*     m_input            = nullptr;
        KeyboardInput*   m_keyboard         = nullptr;

        std::vector<std::string> m_archetype_names;

        //editor flag
        bool        m_b_open        = true;
        std::string m_editor_label  = "";
        int         m_command_index = 0;

        bool        m_will_open_space    = false;
        std::string m_initial_space_name = "";

        bool m_show_readme  = false;
        bool m_show_about   = false;
        bool m_show_license = false;
        bool m_show_credit  = false;

        TextureResource* m_logo_texture = nullptr;
        ImVec2           m_uv_min       = ImVec2(0.0f, 0.0f);                   // Top-left
        ImVec2           m_uv_max       = ImVec2(1.0f, 1.0f);                   // Lower-right
        ImVec4           m_tint_col     = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // No tint
        ImVec4           m_border_col   = ImVec4(1.0f, 1.0f, 1.0f, 0.0f); 

        //imgui flag
        ImGuiDockNodeFlags m_dock_space_flags = ImGuiDockNodeFlags_None;
        ImGuiWindowFlags   m_window_flags     = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    };
}
