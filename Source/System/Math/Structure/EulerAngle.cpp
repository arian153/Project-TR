/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include "EulerAngle.hpp"

namespace GAM400
{

    EulerAngle::EulerAngle(Real x, Real y, Real z)
        : x_rotation(x), y_rotation(y), z_rotation(z)
    {
    }

    EulerAngle::EulerAngle(const EulerAngle& rhs)
        : x_rotation(rhs.x_rotation), y_rotation(rhs.y_rotation), z_rotation(rhs.z_rotation)
    {
    }

    EulerAngle::~EulerAngle()
    {
    }

    EulerAngle& EulerAngle::operator=(const EulerAngle& rhs)
    {
        if (this != &rhs)
        {
            x_rotation = rhs.x_rotation;
            y_rotation = rhs.y_rotation;
            z_rotation = rhs.z_rotation;
        }
        return *this;
    }
}