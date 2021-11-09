#include "TerrainSpace.hpp"

#include "../../../Math/Primitive/Others/Ray.hpp"

namespace GAM400
{
    TerrainAABB::TerrainAABB()
    {
    }

    TerrainAABB::~TerrainAABB()
    {
    }

    void TerrainAABB::Set(const Vector3& min, const Vector3& max)
    {
        m_min = min;
        m_max = max;
    }

    bool TerrainAABB::Intersect(TerrainAABB* aabb) const
    {
        // if separated in x direction
        if (m_min.x > aabb->m_max.x || aabb->m_min.x > m_max.x)
            return false;
        // if separated in y direction
        if (m_min.y > aabb->m_max.y || aabb->m_min.y > m_max.y)
            return false;
        // if separated in z direction
        if (m_min.z > aabb->m_max.z || aabb->m_min.z > m_max.z)
            return false;

        // no separation, must be intersecting
        return true;
    }

    bool TerrainAABB::Intersect(const TerrainAABB& aabb) const
    {
        // if separated in x direction
        if (m_min.x > aabb.m_max.x || aabb.m_min.x > m_max.x)
            return false;
        // if separated in y direction
        if (m_min.y > aabb.m_max.y || aabb.m_min.y > m_max.y)
            return false;
        // if separated in z direction
        if (m_min.z > aabb.m_max.z || aabb.m_min.z > m_max.z)
            return false;
        // no separation, must be intersecting
        return true;
    }

    bool TerrainAABB::Contains(const Vector3& point) const
    {
        if (m_min.x > point.x || point.x > m_max.x)
        {
            return false;
        }
        if (m_min.y > point.y || point.y > m_max.y)
        {
            return false;
        }
        if (m_min.z > point.z || point.z > m_max.z)
        {
            return false;
        }
        return true;
    }

    bool TerrainAABB::Contains(TerrainAABB* aabb) const
    {
        if (this->Intersect(aabb) == true)
        {
            if (m_min.x > aabb->m_min.x || aabb->m_max.x > m_max.x)
            {
                return false;
            }
            if (m_min.y > aabb->m_min.y || aabb->m_max.y > m_max.y)
            {
                return false;
            }
            if (m_min.z > aabb->m_min.z || aabb->m_max.z > m_max.z)
            {
                return false;
            }
            return true;
        }
        return false;
    }

    bool TerrainAABB::Contains(const TerrainAABB& aabb) const
    {
        if (this->Intersect(aabb) == true)
        {
            if (m_min.x > aabb.m_min.x || aabb.m_max.x > m_max.x)
            {
                return false;
            }
            if (m_min.y > aabb.m_min.y || aabb.m_max.y > m_max.y)
            {
                return false;
            }
            if (m_min.z > aabb.m_min.z || aabb.m_max.z > m_max.z)
            {
                return false;
            }
            return true;
        }
        return false;
    }

    bool TerrainAABB::TestRayIntersection(const Ray& ray, Real& t, Real max_distance) const
    {
        // do tests against three sets of planes
        Real    t_min, t_max, t_y_min, t_y_max, t_z_min, t_z_max;
        Vector3 box_min = m_min;
        Vector3 box_max = m_max;
        Vector3 inv_dir;
        inv_dir.x = 1.0f / ray.direction.x;
        inv_dir.y = 1.0f / ray.direction.y;
        inv_dir.z = 1.0f / ray.direction.z;
        if (inv_dir.x > 0.0f)
        {
            t_min = (box_min.x - ray.position.x) * inv_dir.x;
            t_max = (box_max.x - ray.position.x) * inv_dir.x;
        }
        else
        {
            t_min = (box_max.x - ray.position.x) * inv_dir.x;
            t_max = (box_min.x - ray.position.x) * inv_dir.x;
        }
        if (inv_dir.y > 0.0f)
        {
            t_y_min = (box_min.y - ray.position.y) * inv_dir.y;
            t_y_max = (box_max.y - ray.position.y) * inv_dir.y;
        }
        else
        {
            t_y_min = (box_max.y - ray.position.y) * inv_dir.y;
            t_y_max = (box_min.y - ray.position.y) * inv_dir.y;
        }
        if ((t_min > t_y_max) || (t_y_min > t_max))
        {
            return false;
        }
        if (t_y_min > t_min)
        {
            t_min = t_y_min;
        }
        if (t_y_max < t_max)
        {
            t_max = t_y_max;
        }
        if (inv_dir.z > 0.0f)
        {
            t_z_min = (box_min.z - ray.position.z) * inv_dir.z;
            t_z_max = (box_max.z - ray.position.z) * inv_dir.z;
        }
        else
        {
            t_z_min = (box_max.z - ray.position.z) * inv_dir.z;
            t_z_max = (box_min.z - ray.position.z) * inv_dir.z;
        }
        if ((t_min > t_z_max) || (t_z_min > t_max))
        {
            return false;
        }
        if (t_z_min > t_min)
        {
            t_min = t_z_min;
        }
        if (t_z_max < t_max)
        {
            t_max = t_z_max;
        }
        if (t_min < 0.0f && t_max < 0.0f)
        {
            return false;
        }
        t = t_min;
        if (t_min < 0.0f && t_max < 0.0f)
        {
            return false;
        }
        if (t <= 0.0f)
        {
            t = 0.0f;
        }
        // check max distance.
        if (t > max_distance && max_distance >= 0.0f)
        {
            return false;
        }
        // done, have intersection
        return true;
    }

    Real TerrainAABB::Volume() const
    {
        return (m_max.x - m_min.x) * (m_max.y - m_min.y) * (m_max.z - m_min.z);
    }

    Vector3 TerrainAABB::Center() const
    {
        return 0.5f * (m_max + m_min);
    }

    Vector3 TerrainAABB::Size() const
    {
        return m_max - m_min;
    }

    Vector3 TerrainAABB::HalfSize() const
    {
        return 0.5f * (m_max - m_min);
    }

    Vector3 TerrainAABB::Min() const
    {
        return m_min;
    }

    Vector3 TerrainAABB::Max() const
    {
        return m_max;
    }

    TerrainAABB TerrainAABB::Union(const TerrainAABB& aabb) const
    {
        TerrainAABB result;
        result.m_min = this->m_min;
        result.m_max = this->m_max;
        if (aabb.m_min.x < this->m_min.x)
        {
            result.m_min.x = aabb.m_min.x;
        }
        if (aabb.m_min.y < this->m_min.y)
        {
            result.m_min.y = aabb.m_min.y;
        }
        if (aabb.m_min.z < this->m_min.z)
        {
            result.m_min.z = aabb.m_min.z;
        }
        if (aabb.m_max.x > this->m_max.x)
        {
            result.m_max.x = aabb.m_max.x;
        }
        if (aabb.m_max.y > this->m_max.y)
        {
            result.m_max.y = aabb.m_max.y;
        }
        if (aabb.m_max.z > this->m_max.z)
        {
            result.m_max.z = aabb.m_max.z;
        }
        return result;
    }

    SpaceNode* TerrainAABB::GetSpaceNode() const
    {
        return m_node;
    }

    SpaceNode::SpaceNode()
    {
    }

    SpaceNode::~SpaceNode()
    {
    }

    bool SpaceNode::IsLeaf() const
    {
        //Space node always contain 4 child node,
        //so it check only one of child node
        //to determine whether it is leaf or not
        return children[0] == nullptr;
    }

    TerrainSpace::TerrainSpace()
    {
    }

    TerrainSpace::~TerrainSpace()
    {
    }

    void TerrainSpace::Initialize()
    {
    }

    void TerrainSpace::Update(Real dt)
    {
    }

    void TerrainSpace::Shutdown()
    {
    }

    void TerrainSpace::Clear()
    {
    }

    void TerrainSpace::Release()
    {
    }

    void TerrainSpace::Render(PrimitiveRenderer* primitive_renderer)
    {
    }

    SubTerrain* TerrainSpace::Pick(const Vector3& point) const
    {
        return nullptr;
    }

    void TerrainSpace::Query(const TerrainAABB& aabb, std::vector<SubTerrain*>& output) const
    {
    }
}
