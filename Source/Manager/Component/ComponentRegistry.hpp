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
#include <string>
#include <list>
#include <unordered_map>

namespace GAM400
{
    class ComponentFactory;

    class ComponentRegistry
    {
    public:
        ComponentRegistry();
        ~ComponentRegistry();

        bool Initialize();
        bool Shutdown();
        bool AddFactory(ComponentFactory* factory);

    private:
        std::unordered_map<std::string, ComponentFactory*> m_factories;
        std::list<std::string>                             m_keys;

        friend class ComponentManager;

    private:
    };
}
