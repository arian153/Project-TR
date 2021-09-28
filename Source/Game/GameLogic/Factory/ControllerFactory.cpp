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
