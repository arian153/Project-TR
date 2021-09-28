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
