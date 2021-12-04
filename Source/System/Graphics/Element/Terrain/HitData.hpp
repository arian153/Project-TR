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
