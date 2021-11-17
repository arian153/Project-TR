#include "HitData.hpp"

namespace GAM400
{
    HitData::HitData(const Ray& ray)
        : ray(ray)
    {
    }

    bool HitData::operator<(const HitData& rhs) const
    {
        return t > rhs.t;
    }

    HitData& HitData::operator=(const HitData& rhs)
    {
        if (this != &rhs)
        {
            ray          = rhs.ray;
            sub_terrain  = rhs.sub_terrain;
            hit          = rhs.hit;
            t            = rhs.t;
            intersection = rhs.intersection;
            normal       = rhs.normal;
            closest_idx  = rhs.closest_idx;
            face_idx     = rhs.face_idx;
            node         = rhs.node;
        }
        return *this;
    }
}
