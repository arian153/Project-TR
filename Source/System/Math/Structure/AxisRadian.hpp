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
#include "../Utility/MathDef.hpp"
#include "../Algebra/Vector3.hpp"
#include "../Utility/VectorDef.hpp"

namespace GAM400
{
    class AxisRadian
    {
    public:
        explicit AxisRadian(const Vector3& axis = Math::Vector3::Y_AXIS, Real radian = 0.0f);
        AxisRadian(const AxisRadian& rhs);
        ~AxisRadian();

        AxisRadian& operator=(const AxisRadian& rhs);

    public:
        Vector3 axis;
        Real    radian;
    };
}
