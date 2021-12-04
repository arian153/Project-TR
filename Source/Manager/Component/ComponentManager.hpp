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
#include <unordered_map>

namespace GAM400
{
    class Space;
    class Object;
    class Component;
    class ComponentRegistry;

    class ComponentManager
    {
    public:
        ComponentManager();
        ~ComponentManager();

        void Initialize(ComponentRegistry* registry, Space* space);
        void Shutdown();

        Component* Create(const std::string& type, Object* owner);
        Component* Clone(Component* origin, Object* dest);
        Component* Find(const std::string& type, Object* owner);
        void       Find(const std::string& type, std::vector<Component*>& components);
        void       Remove(Component* component);
        void       Remove(Component* component, Object* owner);
        void       Remove(Object* owner);
        void       Clear();


    private:
        std::unordered_multimap<Object*, Component*> m_components;
        ComponentRegistry*                           m_registry = nullptr;
        Space*                                       m_space    = nullptr;
    };
}
