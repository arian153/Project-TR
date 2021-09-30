#pragma once
#include "../ComponentFactory.hpp"

namespace GAM400
{
    class Component;
    class Object;

    class TerrainFactory final : public ComponentFactory
    {
    public:
        TerrainFactory();
        ~TerrainFactory();

        Component* Create(Object* owner, Space* space) override;
        Component* Clone(Component* origin, Object* dest, Space* space) override;
    };
}
