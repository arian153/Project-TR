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
#include "../../External/imgui/imgui.h"
#include "../Math/Utility/MathDef.hpp"

namespace GAM400
{
    class GameEditor;
    class RendererCommon;
    class Application;

    class GUISystem
    {
    public:
        explicit GUISystem(ImGuiIO& io);
        ~GUISystem();

        void Initialize(Application* application);
        void Shutdown();

        void Update(Real dt);

        void BeginRender() const;
        void EndRender() const;

        static bool IsFocusGUI();
        static void CreateGUIContext();
        static void SetFocusFree(bool flag);

        void AddGUI(GameEditor* game_editor);
        void StyleVisualStudio();

    private:
        ImGuiIO&           m_im_gui_io;
        inline static bool m_b_free_focus = false;
        RendererCommon*    m_renderer      = nullptr;
        GameEditor*        m_game_editor   = nullptr;
    };
}
