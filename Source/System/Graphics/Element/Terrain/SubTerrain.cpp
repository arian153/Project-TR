#include "SubTerrain.hpp"

#include "HitData.hpp"
#include "../../../Math/Primitive/Others/Ray.hpp"
#include "../../../Math/Utility/Utility.hpp"
#include "../../../Math/Utility/Utility.inl"
#include "../../DataType/MeshData.hpp"

namespace GAM400
{
    TerrainFace::TerrainFace(U32 a, U32 b, U32 c, const MeshData& terrain_data)
        : idx_a(a), idx_b(b), idx_c(c)
    {
        vertex_a = terrain_data.vertices[a].GetPosition();
        vertex_b = terrain_data.vertices[b].GetPosition();
        vertex_c = terrain_data.vertices[c].GetPosition();
    }

    void TerrainFace::Update(const MeshData& terrain_data)
    {
        vertex_a = terrain_data.vertices[idx_a].GetPosition();
        vertex_b = terrain_data.vertices[idx_b].GetPosition();
        vertex_c = terrain_data.vertices[idx_c].GetPosition();
    }

    bool TerrainFace::HasIntersection(const Ray& ray, Real& t) const
    {
        Vector3 edge_ab = vertex_b - vertex_a;
        Vector3 edge_ac = vertex_c - vertex_a;
        Vector3 h       = CrossProduct(ray.direction, edge_ac);
        float   a       = DotProduct(edge_ab, h);

        if (Math::IsZero(a))
        {
            return false;
        }

        float   f = 1.0f / a;
        Vector3 s = ray.position - vertex_a;
        float   u = f * (DotProduct(s, h));
        if (u < 0.0f || u > 1.0f)
        {
            return false;
        }
        Vector3 q = CrossProduct(s, edge_ab);
        float   v = f * DotProduct(ray.direction, q);
        if (v < 0.0f || u + v > 1.0f)
        {
            return false;
        }
        t = f * DotProduct(edge_ac, q);
        if (t > 0.0f)
        {
            return true;
        }
        return false;
    }

    Vector3 TerrainFace::Normal() const
    {
        Vector3 edge_ab = vertex_b - vertex_a;
        Vector3 edge_ac = vertex_c - vertex_a;
        return CrossProduct(edge_ab, edge_ac).Normalize();
    }

    U32 TerrainFace::ClosestIDX(const Vector3& point) const
    {
        Real da = point.DistanceSquaredTo(vertex_a);
        Real db = point.DistanceSquaredTo(vertex_b);
        Real dc = point.DistanceSquaredTo(vertex_c);

        return da < db ? (da < dc ? idx_a : idx_c) : (db < dc ? idx_b : idx_c);
    }

    SubTerrain::SubTerrain()
    {
    }

    SubTerrain::~SubTerrain()
    {
    }

    void SubTerrain::AddFace(U32 a, U32 b, U32 c, const MeshData& terrain_data)
    {
        faces.emplace_back(a, b, c, terrain_data);
    }

    void SubTerrain::Update(const MeshData& terrain_data)
    {
        //reset y range [flt_max : -flt_max]
        min_y = Math::REAL_POSITIVE_MAX;
        max_y = Math::REAL_NEGATIVE_MAX;
        for (auto& face : faces)
        {
            face.Update(terrain_data);
            min_y = Math::Min(Math::Min(Math::Min(face.vertex_a.y, face.vertex_b.y), face.vertex_c.y), min_y);
            max_y = Math::Max(Math::Max(Math::Max(face.vertex_a.y, face.vertex_b.y), face.vertex_c.y), max_y);
        }
    }

    void SubTerrain::CastRay(HitData& result, Real max_distance)
    {
        result.sub_terrain = this;

        Real   minimum_t = -1.0f;
        size_t idx       = -1;
        if (HasIntersection(result.ray, minimum_t, idx) == true)
        {
            result.t   = minimum_t;
            result.hit = true;
            //ray cast done
            result.intersection = result.ray.position + result.ray.direction * result.t;
            result.normal       = GetNormal(idx);
            result.closest_idx  = GetVertexIDX(idx, result.intersection);
            if (result.t > max_distance && max_distance >= 0.0f)
            {
                result.hit = false;
            }
        }
    }

    bool SubTerrain::HasIntersection(const Ray& ray, Real& t, size_t& idx) const
    {
        t        = Math::REAL_POSITIVE_MAX;
        bool hit = false;

        idx         = -1;
        size_t size = faces.size();

        for (size_t i = 0; i < size; ++i)
        {
            Real new_t;
            if (faces[i].HasIntersection(ray, new_t))
            {
                hit = true;
                if (new_t < t)
                {
                    t   = new_t;
                    idx = i;
                }
            }
        }

        return hit;
    }

    Vector3 SubTerrain::GetNormal(size_t idx)
    {
        if (faces.size() > idx)
        {
            return faces[idx].Normal();
        }
        return Vector3();
    }

    U32 SubTerrain::GetVertexIDX(size_t face_idx, const Vector3& point)
    {
        if (faces.size() > face_idx)
        {
            return faces[face_idx].ClosestIDX(point);
        }
        return 0;
    }
}
