/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include "Component.hpp"

namespace GAM400
{
    Component::Component(Object* owner)
        : m_owner(owner)
    {
    }

    Component::~Component()
    {
    }

    String Component::Type() const
    {
        return m_type;
    }

    const char* Component::TypeCStr() const
    {
        return m_type.c_str();
    }

    bool Component::IsLoaded() const
    {
        return m_b_loaded;
    }

    bool Component::IsUnloaded() const
    {
        return m_b_unloaded;
    }

    Object* Component::GetOwner() const
    {
        return m_owner;
    }

    Space* Component::GetSpace() const
    {
        return m_space;
    }

    void Component::SetSpace(Space* space)
    {
        m_space = space;
    }
}
