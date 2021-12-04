/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include "TerrainFactory.hpp"
#include "../EngineComponent/TerrainComponent.hpp"

namespace GAM400
{
    TerrainFactory::TerrainFactory()
    {
        type = typeid(TerrainComponent).name();
    }

    TerrainFactory::~TerrainFactory()
    {
    }

    Component* TerrainFactory::Create(Object* owner, Space* space)
    {
        auto create = new TerrainComponent(owner);
        create->m_type = type;
        create->SetSpace(space);
        return create;
    }

    Component* TerrainFactory::Clone(Component* origin, Object* dest, Space* space)
    {
        auto source = static_cast<TerrainComponent*>(origin);
        auto cloned = static_cast<TerrainComponent*>(this->Create(dest, space));
        cloned->Clone(source);
        return cloned;
    }
}
