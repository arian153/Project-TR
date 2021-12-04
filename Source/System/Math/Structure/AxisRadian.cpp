/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include "AxisRadian.hpp"

namespace GAM400
{
    AxisRadian::AxisRadian(const Vector3& axis, Real radian)
        : axis(axis), radian(radian)
    {
    }

    AxisRadian::AxisRadian(const AxisRadian& rhs)
        : axis(rhs.axis), radian(rhs.radian)
    {
    }

    AxisRadian::~AxisRadian()
    {
    }

    AxisRadian& AxisRadian::operator=(const AxisRadian& rhs)
    {
        if (this != &rhs)
        {
            axis = rhs.axis;
            radian = rhs.radian;
        }
        return *this;
    }
}