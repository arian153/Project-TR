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
#include "../../Algebra/Vector3.hpp"
#include "../../Algebra/Quaternion.hpp"
#include "../../Structure/Vector3Pair.hpp"

namespace GAM400
{
    class Line
    {
    public:
        explicit Line(const Vector3& position = Vector3(), const Vector3& direction = Math::Vector3::Y_AXIS);
        Line(const Line& rhs);
        ~Line();
        Vector3     ParamToPoint(Real t) const;
        Real        PointToParam(const Vector3& point_on_line) const;
        Line        GetReflectedLine(const Vector3& normal, const Vector3& new_position) const;
        Vector3     SymmetricPoint(const Vector3& point) const;
        Vector3     ClosestPoint(const Vector3& point) const;
        Real        Distance(const Vector3& point, Real& t) const;
        Real        DistanceSquared(const Vector3& point, Real& t) const;
        Vector3Pair ClosestPoint(const Line& line) const;

        Line& operator=(const Line& rhs);
        bool  operator==(const Line& rhs) const;
        bool  operator!=(const Line& rhs) const;

    public:
        Vector3 position;
        Vector3 direction;
    };
}
