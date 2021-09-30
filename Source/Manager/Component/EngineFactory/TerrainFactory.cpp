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
