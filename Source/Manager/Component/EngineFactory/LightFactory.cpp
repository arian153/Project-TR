/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include "LightFactory.hpp"
#include "../EngineComponent/LightComponent.hpp"

namespace GAM400
{
    LightFactory::LightFactory()
    {
        type = typeid(LightComponent).name();
    }

    LightFactory::~LightFactory()
    {
    }

    Component* LightFactory::Create(Object* owner, Space* space)
    {
        auto create = new LightComponent(owner);
        create->m_type = type;
        create->SetSpace(space);
        return create;
    }

    Component* LightFactory::Clone(Component* origin, Object* dest, Space* space)
    {
        auto source = static_cast<LightComponent*>(origin);
        auto cloned = static_cast<LightComponent*>(this->Create(dest, space));
        cloned->Clone(source);
        return cloned;
    }
}
