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
        TerrainFace()  = default;
        ~TerrainFace() = default;

        TerrainFace(U32 a, U32 b, U32 c, const MeshData& terrain_data);
        void Update(const MeshData& terrain_data);
        bool HasIntersection(const Ray& ray, Real& t) const;

    public:
        Vector3 vertex_a, vertex_b, vertex_c;
        U32     idx_a,    idx_b,    idx_c;
    };

    class SubTerrain
    {
    public:
        SubTerrain();
        ~SubTerrain();

        void AddFace(U32 a, U32 b, U32 c, const MeshData& terrain_data);
        void Update(const MeshData& terrain_data);
        bool HasIntersection(const Ray& ray, Real& t) const;

    public:
        Real min_y = 0.0f;
        Real max_y = 0.0f;

        std::vector<TerrainFace> faces;
    };
}
