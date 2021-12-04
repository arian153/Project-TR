/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include "RotatingFactory.h"
#include "../../../Manager/Component/Component.hpp"
#include "../Component/RotatingComponent.h"

namespace Game
{
    RotatingFactory::RotatingFactory()
    {
        type = typeid(RotatingComponent).name();
    }

    RotatingFactory::~RotatingFactory()
    {
    }

    GAM400::Component* RotatingFactory::Create(GAM400::Object* owner, GAM400::Space* space)
    {
        auto create = new RotatingComponent(owner);
        create->m_type = type;
        create->SetSpace(space);
        return create;
    }

    GAM400::Component* RotatingFactory::Clone(GAM400::Component* origin, GAM400::Object* dest, GAM400::Space* space)
    {
        auto source = static_cast<RotatingComponent*>(origin);
        auto cloned = static_cast<RotatingComponent*>(this->Create(dest, space));
        cloned->Clone(source);
        return cloned;
    }
}
