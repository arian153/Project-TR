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
#include "..//Component.hpp"

namespace GAM400
{
    class PrimitiveRenderer;
    class TextRenderer;
    class InputCommon;

    class LogicComponent : public Component
    {
    public:
        virtual ~LogicComponent();
        LogicComponent()                                     = delete;
        LogicComponent(const LogicComponent& rhs)            = delete;
        LogicComponent& operator=(const LogicComponent& rhs) = delete;

        virtual void Render() = 0;
    protected:
        explicit LogicComponent(Object* owner);

    private:
        friend class LogicSubsystem;

    protected:
        InputCommon*       m_input              = nullptr;
        TextRenderer*      m_text_renderer      = nullptr;
        PrimitiveRenderer* m_primitive_renderer = nullptr;
    };
}
