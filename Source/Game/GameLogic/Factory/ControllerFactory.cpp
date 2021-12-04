/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include "ControllerFactory.h"
#include "../../../Manager/Component/Component.hpp"
#include "../Component/ControllerComponent.h"

namespace Game
{
    ControllerFactory::ControllerFactory()
    {
        type = typeid(ControllerComponent).name();
    }

    ControllerFactory::~ControllerFactory()
    {
    }

    GAM400::Component* ControllerFactory::Create(GAM400::Object* owner, GAM400::Space* space)
    {
        auto create    = new ControllerComponent(owner);
        create->m_type = type;
        create->SetSpace(space);
        return create;
    }

    GAM400::Component* ControllerFactory::Clone(GAM400::Component* origin, GAM400::Object* dest, GAM400::Space* space)
    {
        auto source = static_cast<ControllerComponent*>(origin);
        auto cloned = static_cast<ControllerComponent*>(this->Create(dest, space));
        cloned->Clone(source);
        return cloned;
    }
}
