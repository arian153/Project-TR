#pragma once
#include "../../../Manager/Component/ComponentFactory.hpp"

namespace Game
{
    class ControllerFactory final : public GAM400::ComponentFactory
    {
    public:
        ControllerFactory();
        ~ControllerFactory();

        GAM400::Component* Create(GAM400::Object* owner, GAM400::Space* space) override;
        GAM400::Component* Clone(GAM400::Component* origin, GAM400::Object* dest, GAM400::Space* space) override;
    };
}
