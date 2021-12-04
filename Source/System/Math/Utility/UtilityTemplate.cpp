/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include "MathDef.hpp"

namespace GAM400
{
    namespace Math 
    {
        template<typename T>
        T Min(const T& a, const T& b)
        {
            return a < b ? a : b;
        }

        template<typename T>
        T Max(const T& a, const T& b)
        {
            return a > b ? a : b;
        }

        template<typename T>
        T Clamp(const T& x, const T& low, const T& high)
        {
            return x < low ? low : (x > high ? high : x);
        }

    }
}