/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include "GameEditor.hpp"
#include "../../../External/imgui/imgui.h"
#include "../../Core/OS-API/Application.hpp"
#include "../../../Manager/Level/LevelManager.hpp"
#include "../../../Manager/Object/ObjectFactory.hpp"
#include "../../../Manager/Object/ObjectManager.hpp"
#include "../../../Manager/Resource/ResourceManager.hpp"
#include "../../../Manager/Resource/ResourceType/JsonResource.hpp"
#include "../../../Manager/Resource/ResourceType/TextureResource.hpp"
#include "../../../Manager/Space/Space.hpp"
#include "../../Core/Input/InputCommon.hpp"
#include "../../Core/Input/KeyboardInput.hpp"
#include "../../Graphics/Common/Texture/TextureCommon.hpp"
#include "Command/EditorCommand.hpp"

namespace
{
    const char json_cpp_license[] = R"(
========================================================================
Copyright (c) 2007-2010 Baptiste Lepilleur and The JsonCpp Authors

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use, copy,
modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
========================================================================
    )";

    const char dx_tex_license[] = R"(
==========================================================================================
                               The MIT License (MIT)

Copyright (c) 2011-2020 Microsoft Corp

Permission is hereby granted, free of charge, to any person obtaining a copy of this 
software and associated documentation files (the "Software"), to deal in the Software 
without restriction, including without limitation the rights to use, copy, modify, 
merge, publish, distribute, sublicense, and/or sell copies of the Software, and to 
permit persons to whom the Software is furnished to do so, subject to the following 
conditions: 

The above copyright notice and this permission notice shall be included in all copies 
or substantial portions of the Software.  

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF 
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

==========================================================================================
    )";

    const char imgui_license[] = R"(
--------------------------------------------------------------------------------------
 The MIT License (MIT)
 
 Copyright (c) 2014-2020 Omar Cornut
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
--------------------------------------------------------------------------------------
    )";
}

namespace GAM400
{
    GameEditor::GameEditor()
    {
    }

    GameEditor::~GameEditor()
    {
    }

    void GameEditor::Initialize(Application* application)
    {
        m_application                = application;
        m_input                      = application->GetInput();
        m_keyboard                   = m_input->GetKeyboardInput();
        m_space_editor.m_game_editor = this;
        m_space_editor.Initialize(application);
        m_window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        m_window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        m_window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        m_command_registry.Initialize();
        m_space_editor.m_command_registry = &m_command_registry;

        m_object_factory   = m_application->GetObjectFactory();
        m_resource_manager = m_application->GetResourceManager();
        m_object_factory->GetArchetypeName(m_archetype_names);

        m_logo_texture = m_resource_manager->GetTextureResource(L"../../Resource/Texture/DigiPen_RED_1024px.png");
    }

    void GameEditor::Update(Real dt)
    {
        if (m_b_open)
        {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->GetWorkPos());
            ImGui::SetNextWindowSize(viewport->GetWorkSize());
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
            ImGui::Begin("GAM 400 Editor", nullptr, m_window_flags);
            ImGui::PopStyleVar(3);
            // DockSpace
            ImGuiIO& io = ImGui::GetIO();
            if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
            {
                ImGuiID dock_space_id = ImGui::GetID("GAM400-Editor");
                ImGui::DockSpace(dock_space_id, ImVec2(0.0f, 0.0f), m_dock_space_flags);
            }
            if (ImGui::BeginMenuBar())
            {
                UpdateFileTab();
                UpdateEditTab();
                //UpdateObjectTab();
                UpdateHelpTab();
                ImGui::EndMenuBar();
            }
            ImGui::End();
            {
                m_space_editor.UpdateSceneWindow(dt);
                m_space_editor.UpdateHierarchyWindow();
                m_space_editor.UpdateInspectorWindow();
                m_space_editor.UpdateSpaceSetting();
                m_level_editor.Update(dt);
                UpdateCommandWindow();
            }
            UpdateShortCuts();
            ShowReadMe();
            ShowLicense();
            ShowAbout();
            ShowCredit();

            if (m_will_open_space)
            {
                m_will_open_space = false;
                m_space_editor.OpenSpace(m_initial_space_name);
            }
        }
    }

    void GameEditor::Shutdown()
    {
        m_command_registry.Shutdown();
    }

    bool GameEditor::IsOpen() const
    {
        return m_b_open;
    }

    void GameEditor::SetOpen(bool is_open)
    {
        m_b_open = is_open;
    }

    CommandRegistry* GameEditor::GetCommandRegistry()
    {
        return &m_command_registry;
    }

    void GameEditor::SetInitialEditSpace(const std::string& space)
    {
        m_will_open_space    = true;
        m_initial_space_name = space;
    }

    void GameEditor::UpdateFileTab()
    {
        if (ImGui::BeginMenu("File"))
        {
            size_t open_count = m_space_editor.OpenCount();
            //if (ImGui::BeginMenu("New - Not Implemented Yet"))
            //{
            //    ImGui::EndMenu();
            //}
            if (ImGui::BeginMenu("Open"))
            {
                if (ImGui::BeginMenu("Space", open_count < m_space_editor.Size()))
                {
                    m_space_editor.OpenSequence();
                    ImGui::EndMenu();
                }
                ImGui::EndMenu();
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Close", nullptr, false, open_count > 0))
            {
                m_space_editor.CloseSequence();
            }
            if (ImGui::MenuItem("Close All", nullptr, false, open_count > 0))
            {
                m_space_editor.CloseAllSequence();
            }
            //ImGui::Separator();
            //if (ImGui::MenuItem("Save - Not Implemented Yet", nullptr, false, open_count > 0))
            //{
            //}
            //if (ImGui::MenuItem("Save All - Not Implemented Yet", nullptr, false, open_count > 0))
            //{
            //}
            ImGui::Separator();
            if (ImGui::MenuItem("Exit"))
            {
                m_application->GetLevelManager()->SetQuit();
            }
            ImGui::EndMenu();
        }
    }

    void GameEditor::UpdateEditTab()
    {
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z"))
            {
                m_command_registry.UndoCommand();
            }
            if (ImGui::MenuItem("Redo", "CTRL+Y"))
            {
                m_command_registry.RedoCommand();
            }
            //ImGui::Separator();
            //if (ImGui::MenuItem("Cut - Not Implemented Yet"))
            //{
            //}
            //if (ImGui::MenuItem("Copy - Not Implemented Yet"))
            //{
            //}
            //if (ImGui::MenuItem("Paste - Not Implemented Yet"))
            //{
            //}
            //if (ImGui::MenuItem("Duplicate - Not Implemented Yet"))
            //{
            //}
            //if (ImGui::MenuItem("Delete - Not Implemented Yet"))
            //{
            //}
            ImGui::EndMenu();
        }
    }

    void GameEditor::UpdateObjectTab()
    {
        if (ImGui::BeginMenu("Object"))
        {
            if (ImGui::BeginMenu("Create Object"))
            {
                size_t size = m_archetype_names.size();

                for (size_t i = 0; i < size; ++i)
                {
                    if (ImGui::MenuItem(("Create " + m_archetype_names[i]).c_str()))
                    {
                        if (m_space_editor.m_editing_space != nullptr)
                        {
                            m_space_editor.m_editing_space->GetObjectManager()->AddObject(m_archetype_names[i], i);
                        }
                    }
                }
                ImGui::EndMenu();
            }
            ImGui::Separator();
            ImGui::EndMenu();
        }
    }

    void GameEditor::UpdateHelpTab()
    {
        if (ImGui::BeginMenu("Help"))
        {
            ImGui::MenuItem("Read Me", nullptr, &m_show_readme);
            ImGui::MenuItem("Credit", nullptr, &m_show_credit);
            ImGui::MenuItem("License", nullptr, &m_show_license);
            ImGui::MenuItem("About", nullptr, &m_show_about);

            ImGui::EndMenu();
        }
    }

    static bool Items_CommandGetter(void* data, int idx, const char** out_text)
    {
        auto& commands = *static_cast<std::vector<EditorCommand*>*>(data);
        if (idx < 0 || idx >= static_cast<int>(commands.size()))
        {
            return false;
        }
        *out_text = commands[idx]->TypeCStr();
        return true;
    }

    void GameEditor::UpdateCommandWindow()
    {
        ImGui::Begin("Commands");
        ImVec2 min = ImGui::GetWindowContentRegionMin();
        ImVec2 max = ImGui::GetWindowContentRegionMax();
        ImGui::PushItemWidth(max.x - min.x);
        auto commands = m_command_registry.m_command_registry;
        if (ImGui::ListBox(
                           "##CommandsObjectList", &m_command_index, Items_CommandGetter,
                           static_cast<void*>(&commands), static_cast<int>(commands.size()), (int)m_command_registry.m_registry_size))
        {
        }
        ImGui::End();
    }

    void GameEditor::ShowReadMe()
    {
        if (m_show_readme)
        {
            if (ImGui::Begin("Read Me", &m_show_readme))
            {
                ImGui::BeginGroup();
                ImGui::BeginChild("Usage", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()));

                ImGui::Text("Usage");
                ImGui::Text("1. Click File Tab, and Open Space.");
                ImGui::Text("2. Camera Control");
                ImGui::Text("    Hold Mouse LB & move - Change camera view direction on spherically");
                ImGui::Text("    Roll Mouse Wheel     - Change spherical camera's radius on same view");
                ImGui::Text("    Press W, S           - Change camera position Front and Back");
                ImGui::Text("    Press A, D           - Change camera position Left and Right");
                ImGui::Text("    Press R, F           - Change camera position Up and Down");
                ImGui::Text("3. Terrain Editing");
                ImGui::Text("   Press Mouse RB        - Select Vertex on Terrain");
                ImGui::Text("    Hold Mouse RB & move - Edit Vertex or Apply Terrain Brush");
                ImGui::Text("4. Export Terrain");
                ImGui::Text("   Press Export PPM or OBJ Button on Inspector Window");
                ImGui::Text(R"(   You can find exported file in "Documents\TRGP Output\")");

                ImGui::EndChild();
                if (ImGui::Button("Close"))
                {
                    m_show_readme = false;
                }
                ImGui::EndGroup();
                ImGui::End();
            }
        }
    }

    void GameEditor::UpdateShortCuts()
    {
        ImGuiIO& io = ImGui::GetIO();
        if (io.KeyCtrl && ImGui::IsKeyPressed(io.KeyMap[ImGuiKey_Z]))
        {
            m_command_registry.UndoCommand();
        }
        if (io.KeyCtrl && ImGui::IsKeyPressed(io.KeyMap[ImGuiKey_Y]))
        {
            m_command_registry.RedoCommand();
        }
    }

    void GameEditor::ShowLicense()
    {
        if (m_show_license)
        {
            if (ImGui::Begin("License", &m_show_license))
            {
                ImGui::BeginGroup();
                ImGui::BeginChild("License", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()));

                ImGui::Text("Open Source License");
                if (ImGui::CollapsingHeader("jsoncpp"))
                {
                    ImGui::Text(json_cpp_license);
                }
                if (ImGui::CollapsingHeader("DirectXTex texture processing library"))
                {
                    ImGui::Text(dx_tex_license);
                }
                if (ImGui::CollapsingHeader("Dear ImGui"))
                {
                    ImGui::Text(imgui_license);
                }

                ImGui::EndChild();
                if (ImGui::Button("Close"))
                {
                    m_show_license = false;
                }
                ImGui::EndGroup();

                ImGui::End();
            }
        }
    }

    void GameEditor::ShowAbout()
    {
        if (m_show_about)
        {
            if (ImGui::Begin("About", &m_show_about))
            {
                ImGui::BeginGroup();
                ImGui::BeginChild("About", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()));

                ImGui::NewLine();
                ImGui::NewLine();
                ImGui::NewLine();

                ImVec2 min         = ImGui::GetWindowContentRegionMin();
                ImVec2 max         = ImGui::GetWindowContentRegionMax();
                Real   scene_scale = max.x - min.x;
                Real   ratio       = 0.241211f;
                ImVec2 size        = ImVec2(scene_scale, scene_scale * ratio);
                ImGui::Image(
                             m_logo_texture->GetTexture()->GetTexture(), size,
                             m_uv_min, m_uv_max, m_tint_col, m_border_col);

                ImGui::NewLine();
                ImGui::NewLine();
                ImGui::Text("Terrain Generating & Rendering Project");
                ImGui::Text("Version 1.0.12032021");
                ImGui::Text(R"(All content © 2021 DigiPen (USA) Corporation, all rights reserved.)");

                ImGui::EndChild();
                if (ImGui::Button("Close"))
                {
                    m_show_about = false;
                }
                ImGui::EndGroup();
                ImGui::End();
            }
        }
    }

    void GameEditor::ShowCredit()
    {
        if (m_show_credit)
        {
            if (ImGui::Begin("Credit", &m_show_credit))
            {
                ImGui::BeginGroup();
                ImGui::BeginChild("Credit", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()));

                ImGui::Text("Credit");
                ImGui::NewLine();
                ImGui::NewLine();
                ImGui::Text("Tech Lead");
                ImGui::Text(" Eric Han");
                ImGui::NewLine();
                ImGui::Text("Graphics Programming");
                ImGui::Text(" Eric Han");
                ImGui::NewLine();
                ImGui::Text("Tool Programming");
                ImGui::Text(" Eric Han");
                ImGui::NewLine();

                ImGui::Text("Faculty & Advisors");
                ImGui::Text(" Andrew Kaplan");
                ImGui::Text(" Jen Sward");
                ImGui::Text(" Kai Tagawa");
                ImGui::NewLine();

                ImGui::Text("Created at");
                ImGui::Text(" DigiPen Institute of Technology");
                ImGui::NewLine();

                ImGui::Text("PRESIDENT");
                ImGui::Text(" CLAUDE COMAIR");
                ImGui::NewLine();

                ImGui::Text("EXECUTIVES");
                ImGui::Text(" JASON CHU");
                ImGui::Text(" SAMIR ABOU SAMRA   ");
                ImGui::Text(" MICHELE COMAIR");
                ImGui::Text(" ANGELA KUGLER   ");
                ImGui::Text(" ERIK MOHRMANN");
                ImGui::Text(" BENJAMIN ELLINGER");
                ImGui::Text(" MELVIN GONSALVEZ");
                ImGui::NewLine();

                ImGui::Text(R"(All content © 2021 DigiPen (USA) Corporation, all rights reserved.)");

                ImGui::EndChild();
                if (ImGui::Button("Close"))
                {
                    m_show_credit = false;
                }
                ImGui::EndGroup();
                ImGui::End();
            }
        }
    }
}
