/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include "TransformFactory.hpp"
#include "../EngineComponent/TransformComponent.hpp"

namespace GAM400
{
    TransformFactory::TransformFactory()
    {
        type = typeid(TransformComponent).name();
    }

    TransformFactory::~TransformFactory()
    {
    }

    Component* TransformFactory::Create(Object* owner, Space* space)
    {
        auto create = new TransformComponent(owner);
        create->m_type = type;
        create->SetSpace(space);
        return create;
    }

    Component* TransformFactory::Clone(Component* origin, Object* dest, Space* space)
    {
        auto source = static_cast<TransformComponent*>(origin);
        auto cloned = static_cast<TransformComponent*>(this->Create(dest, space));
        cloned->Clone(source);
        return cloned;
    }
}
