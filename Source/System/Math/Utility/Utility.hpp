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
#include "MathDef.hpp"


namespace GAM400
{
    class Vector3;
    class Vector3Pair;

    namespace Math
    {
        Real        LinearInterpolation(Real v0, Real v1, Real t);
        Real        SmoothStart(Real t);
        Real        SmoothStop(Real t);
        Vector3Pair GetTangentUsingQuaternion(const GAM400::Vector3& normal);
        bool SolveQuadratic(Real a, Real b, Real c, Real& result1, Real& result2);

        template <typename T>
        T Min(const T& a, const T& b);

        template <typename T>
        T Max(const T& a, const T& b);

        template <typename T>
        T Clamp(const T& x, const T& low, const T& high);
    }
}

#include "Utility.inl"
// ReSharper disable once CppUnusedIncludeDirective
#include "UtilityTemplate.cpp"
