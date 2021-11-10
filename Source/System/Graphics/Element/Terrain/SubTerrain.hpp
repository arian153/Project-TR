#pragma once
#include <vector>

#include "../../../Core/Utility/CoreDef.hpp"
#include "../../../Math/Algebra/Vector3.hpp"
#include "../../DataType/MeshInfo.hpp"

namespace GAM400
{
    class MeshData;
    class Ray;

    class TerrainFace
    {
    public:
        TerrainFace() = default;
        ~TerrainFace() = default;

        TerrainFace(U32 a, U32 b, U32 c, MeshData* terrain_data);
        void Update(MeshData* terrain_data);
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

        void Update(MeshData* terrain_data);
        bool HasIntersection(const Ray& ray, Real& t) const;

    private:
        std::vector<TerrainFace> faces;
    };
}
