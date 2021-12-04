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
#include "../../Math/Algebra/Vector3.hpp"
#include "../../Math/Primitive/Others/Ray.hpp"
#include <vector>

namespace GAM400
{
    class Primitive;

    class PrimitiveHitData
    {
    public:
        bool              operator<(const PrimitiveHitData& rhs) const;
        PrimitiveHitData& operator=(const PrimitiveHitData& rhs);

    public:
        Primitive* primitive = nullptr;
        bool       hit       = false;
        Real       t         = -1.0f;
    };

    class PrimitiveRayCastResult
    {
    public:
        explicit                PrimitiveRayCastResult(const Ray& ray);
        PrimitiveRayCastResult& operator=(const PrimitiveRayCastResult& rhs);

        Vector3 GetLocalIntersection() const;
        Vector3 GetWorldIntersection() const;
        Vector3 GetLocalNormal() const;
        Vector3 GetWorldNormal() const;

    public:
        Ray              ray; //global ray;
        PrimitiveHitData hit_data;
        Vector3          intersection;
        Vector3          normal;
    };

    class PrimitiveRayIntersectionResult
    {
    public:
        explicit         PrimitiveRayIntersectionResult(const Ray& ray);
        PrimitiveHitData GetHitData(size_t i = 0);
        Vector3          GetLocalIntersection(size_t i = 0);
        Vector3          GetWorldIntersection(size_t i = 0);
        Vector3          GetLocalNormal(size_t i = 0);
        Vector3          GetWorldNormal(size_t i = 0);

    public:
        Ray                           ray; //global ray
        std::vector<PrimitiveHitData> hit_list;
    };
}
