/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

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
