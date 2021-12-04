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
#include <vector>

#include "../../../Core/Utility/CoreDef.hpp"
#include "../../../Math/Algebra/Vector3.hpp"
#include "../../DataType/MeshInfo.hpp"

namespace GAM400
{
    class Terrain;
    class TerrainAABB;
    class HitData;
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
        bool HasIntersection(const TerrainAABB& aabb) const;

        void ApplyAddition(Real addition);

        Vector3 Normal() const;
        U32 ClosestIDX(const Vector3& point) const;

        void SetVertex(U32 idx, const Vector3& vertex);
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
        void CastRay(HitData& result, Real max_distance = -1.0f);
        bool HasIntersection(const Ray& ray, Real& t, size_t& idx) const;

        Vector3 GetNormal(size_t idx);
        U32 GetVertexIDX(size_t face_idx, const Vector3& point);

        void Query(const TerrainAABB& aabb, std::vector<TerrainFace*>& output_faces);
        void ApplyAddition(const TerrainAABB& aabb, std::vector<TerrainFace*>& output_faces, Real addition, MeshData& terrain_data);
        void ApplyAddition(Real addition, MeshData& terrain_data);

    public:
        Real min_y = 0.0f;
        Real max_y = 0.0f;

        std::vector<TerrainFace> faces;
    };
}
