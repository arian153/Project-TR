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

namespace GAM400
{
    class EulerAngle
    {
    public:
        explicit EulerAngle(Real x = 0.0f, Real y = 0.0f, Real z = 0.0f);
        EulerAngle(const EulerAngle& rhs);
        ~EulerAngle();
        EulerAngle& operator=(const EulerAngle& rhs);

    public:
        Real x_rotation, y_rotation, z_rotation;
    };
}
