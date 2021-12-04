/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include "Vector3Pair.hpp"

namespace GAM400
{
    Vector3Pair::Vector3Pair(const Vector3& a, const Vector3& b)
        : a(a), b(b)
    {
    }

    Vector3Pair::Vector3Pair(const Vector3Pair& rhs)
        : a(rhs.a), b(rhs.b)
    {
    }

    Vector3Pair& Vector3Pair::operator=(const Vector3Pair& rhs)
    {
        if (this != &rhs)
        {
            a = rhs.a;
            b = rhs.b;
        }
        return *this;
    }
}