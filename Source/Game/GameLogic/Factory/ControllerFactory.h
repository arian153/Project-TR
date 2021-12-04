/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

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
