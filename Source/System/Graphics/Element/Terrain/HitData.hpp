#pragma once
#include "../../../Core/Utility/CoreDef.hpp"
#include "../../../Math/Algebra/Vector3.hpp"
#include "../../../Math/Primitive/Others/Ray.hpp"

namespace GAM400
{
    class SpaceNode;
    class SubTerrain;

    class HitData
    {
    public:
        explicit HitData(const Ray& ray);
        bool     operator<(const HitData& rhs) const;
        HitData& operator=(const HitData& rhs);

    public:
        Ray         ray;
        SubTerrain* sub_terrain = nullptr;
        bool        hit         = false;
        Real        t           = -1.0f;
        Vector3     intersection;
        Vector3     normal;
        U32         closest_idx = 0;
        size_t      face_idx    = 0;
        SpaceNode*  node        = nullptr;
    };
}
