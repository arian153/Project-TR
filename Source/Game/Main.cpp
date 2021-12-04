/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include <iostream>
#include "../System/Core/Core.hpp"
#include "../Manager/Component/ComponentRegistry.hpp"
#include "GameLogic/Factory/ControllerFactory.h"
#include "GameLogic/Factory/RotatingFactory.h"
#include "../Manager/Level/LevelManager.hpp"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR cmd_line, int show_cmd)
{
    E5_LEAK_CHECKS(-1);
    auto app = new GAM400::Application();
    app->Initialize();
    //app->GetLevelManager()->SetInitialLevel("Collider");
    //Add game components
    app->GetComponentRegistry()->AddFactory(new Game::ControllerFactory);
    app->GetComponentRegistry()->AddFactory(new Game::RotatingFactory);

    app->Update();
    app->Shutdown();
    delete app;
    return 0;
}

