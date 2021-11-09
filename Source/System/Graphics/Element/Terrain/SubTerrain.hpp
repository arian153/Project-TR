#pragma once
#include <vector>

#include "../../../Core/Utility/CoreDef.hpp"
#include "../../../Math/Algebra/Vector3.hpp"

namespace GAM400
{
    class Ray;

    class TerrainFace
    {
    public:
        TerrainFace() = default;
        ~TerrainFace() = default;

        TerrainFace(U32 a, U32 b, U32 c);
        bool HasIntersection(const Ray& ray, Real& t) const;

    private:
        Vector3 vertex_a, vertex_b, vertex_c;
        U32     idx_a,    idx_b,    idx_c;
    };

    class SubTerrain
    {
    public:
        SubTerrain();
        ~SubTerrain();

    private:
        std::vector<TerrainFace> faces;
    };
}
