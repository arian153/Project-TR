#include "SubTerrain.hpp"

#include "../../../Math/Primitive/Others/Ray.hpp"
#include "../../../Math/Utility/Utility.inl"

namespace GAM400
{
    TerrainFace::TerrainFace(U32 a, U32 b, U32 c)
        : idx_a(a), idx_b(b), idx_c(c)
    {
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

    SubTerrain::SubTerrain()
    {
    }

    SubTerrain::~SubTerrain()
    {
    }
}
