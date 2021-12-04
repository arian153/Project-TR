/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include "MeshFactory.hpp"
#include "../EngineComponent/MeshComponent.hpp"

namespace GAM400
{
    MeshFactory::MeshFactory()
    {
        type = typeid(MeshComponent).name();
    }

    MeshFactory::~MeshFactory()
    {
    }

    Component* MeshFactory::Create(Object* owner, Space* space)
    {
        auto create = new MeshComponent(owner);
        create->m_type = type;
        create->SetSpace(space);
        return create;
    }

    Component* MeshFactory::Clone(Component* origin, Object* dest, Space* space)
    {
        auto source = static_cast<MeshComponent*>(origin);
        auto cloned = static_cast<MeshComponent*>(Create(dest, space));
        cloned->Clone(source);
        return cloned;
    }
}
