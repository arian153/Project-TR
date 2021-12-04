/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

namespace GAM400
{
    template <typename T>
    T* Object::AddComponent()
    {
        auto type = typeid(T).name();
        auto found = m_component_map.find(type);

        if (found == m_component_map.end())
        {
            auto created = m_component_manager->Create(type, this);
            m_component_map.emplace(type, created);
            m_components.push_back(created);
            created->Initialize();

            return static_cast<T*>(created);
        }

        return nullptr;
    }

    template <typename T>
    bool Object::HasComponent() const
    {
        auto type = typeid(T).name();
        auto found = m_component_map.find(type);

        if (found != m_component_map.end())
            return true;

        return false;
    }

    template <typename T>
    T* Object::GetComponent() const
    {
        auto type = typeid(T).name();
        auto found = m_component_map.find(type);

        if (found != m_component_map.end())
            return static_cast<T*>(found->second);

        return nullptr;
    }

    template <typename T>
    void Object::RemoveComponent()
    {
        auto type = typeid(T).name();
        auto found = m_component_map.find(type);

        if (found != m_component_map.end())
        {
            m_components.erase(std::find(m_components.begin(), m_components.end(), found->second));
            m_component_manager->Remove(found->second, this);
            m_component_map.erase(found);
        }
    }
}