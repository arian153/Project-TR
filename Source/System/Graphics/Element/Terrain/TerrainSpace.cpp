#include "TerrainSpace.hpp"

#include <queue>

#include "HitData.hpp"
#include "../Terrain.hpp"
#include "../../../Math/Primitive/Others/Ray.hpp"
#include "../../../Math/Utility/Utility.hpp"

namespace GAM400
{
    TerrainAABB::TerrainAABB()
    {
    }

    TerrainAABB::TerrainAABB(SpaceNode* node)
        : m_node(node)
    {
    }

    TerrainAABB::~TerrainAABB()
    {
    }

    void TerrainAABB::SetMinMax(const Vector3& min, const Vector3& max)
    {
        m_min = min;
        m_max = max;
    }

    void TerrainAABB::SetCenterHalfSize(const Vector3& center, const Vector3& half_size)
    {
        m_max = center + half_size;
        m_min = center - half_size;
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

    bool TerrainAABB::ContainsExceptY(const Vector3& point) const
    {
        if (m_min.x > point.x || point.x > m_max.x)
        {
            return false;
        }
        if (m_min.z > point.z || point.z > m_max.z)
        {
            return false;
        }
        return true;
    }

    bool TerrainAABB::ContainsExceptY(const Vector3& p0, const Vector3& p1, const Vector3& p2) const
    {
        return ContainsExceptY(p0) || ContainsExceptY(p1) || ContainsExceptY(p2);
    }

    bool TerrainAABB::ContainsExceptY(const TerrainFace& face) const
    {
        return ContainsExceptY(face.vertex_a) || ContainsExceptY(face.vertex_b) || ContainsExceptY(face.vertex_c);
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

    void TerrainAABB::ResetMinMaxY()
    {
        m_min.y = Math::REAL_POSITIVE_MAX;
        m_max.y = Math::REAL_NEGATIVE_MAX;
    }

    void TerrainAABB::SetMinMaxY(Real min, Real max)
    {
        m_min.y = min;
        m_max.y = max;
    }

    void TerrainAABB::ExpandY(Real min, Real max)
    {
        m_min.y = Math::Min(m_min.y, min);
        m_max.y = Math::Max(m_max.y, max);
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
        : aabb(this)
    {
        children[0] = nullptr;
        children[1] = nullptr;
        children[2] = nullptr;
        children[3] = nullptr;
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

    void TerrainSpace::Initialize(Terrain* terrain)
    {
        m_terrain = terrain;
        if (m_root != nullptr)
        {
            Shutdown();
        }

        m_cell_depth = m_terrain->m_terrain_depth;
        m_cell_width = m_terrain->m_terrain_width;

        m_tree_height = 0;
        while (m_cell_depth > m_size_threshold || m_cell_width > m_size_threshold)
        {
            m_cell_depth *= 0.5f;
            m_cell_width *= 0.5f;
            m_tree_height++;
        }

        //build tree structure
        m_root = CreateNode(nullptr);

        Vector3 front = m_terrain->m_grid.vertices.front().GetPosition();
        Vector3 back  = m_terrain->m_grid.vertices.back().GetPosition();
        m_root->aabb.SetMinMax(
                               Vector3(Math::Min(front.x, back.x), 0.0f, Math::Min(front.z, back.z)),
                               Vector3(Math::Max(front.x, back.x), 0.0f, Math::Max(front.z, back.z)));

        size_t size = m_terrain->m_grid.faces.size();
        m_root->sub_terrain.faces.reserve(size);
        for (size_t i = 0; i < size; ++i)
        {
            //Face
            auto& face = m_terrain->m_grid.faces[i];
            m_root->sub_terrain.AddFace(face.a, face.b, face.c, m_terrain->m_grid);
        }

        BuildTreeRecursive(m_root, 0);

        for (auto& node : m_nodes)
        {
            if (node->IsLeaf())
            {
                m_leaves.push_back(node);
            }
        }
    }

    void TerrainSpace::Update()
    {
        std::list<SpaceNode*> aabb_queue;
        for (auto& node : m_nodes)
        {
            node->aabb.ResetMinMaxY();
        }

        for (auto& leaf : m_leaves)
        {
            leaf->sub_terrain.Update(m_terrain->m_grid);
            leaf->aabb.SetMinMaxY(leaf->sub_terrain.min_y, leaf->sub_terrain.max_y);
            aabb_queue.push_back(leaf);
        }

        while (!aabb_queue.empty())
        {
            SpaceNode& node = *aabb_queue.front();
            aabb_queue.pop_front();
            if (node.parent != nullptr)
            {
                node.parent->aabb.ExpandY(node.aabb.Min().y, node.aabb.Max().y);

                auto found = std::find(aabb_queue.begin(), aabb_queue.end(), node.parent);
                if (found == aabb_queue.end())
                {
                    aabb_queue.push_back(node.parent);
                }
            }
        }
    }

    void TerrainSpace::Shutdown()
    {
        for (auto& node : m_nodes)
        {
            delete node;
        }
        m_nodes.clear();
        m_leaves.clear();
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

    void TerrainSpace::CastRay(HitData& result, Real max_distance) const
    {
        std::queue<SpaceNode*> queue;
        if (m_root != nullptr)
        {
            queue.push(m_root);
        }
        Ray ray = result.ray;
        while (!queue.empty())
        {
            SpaceNode& node = *queue.front();
            queue.pop();
            TerrainAABB& aabb   = node.aabb;
            Real         aabb_t = Math::REAL_POSITIVE_MAX;
            if (aabb.TestRayIntersection(ray, aabb_t, max_distance) == true)
            {
                // the node cannot possibly give closer results, skip
                if (result.hit && result.t < aabb_t)
                    continue;
                if (node.IsLeaf() == true)
                {
                    SubTerrain& sub_terrain = node.sub_terrain;
                    HitData     ray_cast_result(ray);
                    sub_terrain.CastRay(ray_cast_result, max_distance);
                    if (ray_cast_result.hit == true)
                    {
                        if (result.hit == true) // compare hit
                        {
                            if (ray_cast_result.t < result.t)
                            {
                                result = ray_cast_result;
                            }
                        }
                        else // first hit
                        {
                            result = ray_cast_result;
                        }
                    }
                }
                else // is branch
                {
                    queue.push(node.children[0]);
                    queue.push(node.children[1]);
                    queue.push(node.children[2]);
                    queue.push(node.children[3]);
                }
            }
        }
    }

    void TerrainSpace::BuildTreeRecursive(SpaceNode* node, int height)
    {
        if (height == m_tree_height)
            return;

        Vector3 center = node->aabb.Center();
        Vector3 scale  = node->aabb.HalfSize();
        Real    x_half = scale.x * 0.5f;
        Real    z_half = scale.z * 0.5f;

        node->children[0] = CreateNode(node);
        node->children[0]->aabb.SetCenterHalfSize(center + Vector3(+x_half, 0.0f, +z_half), scale);
        node->children[1] = CreateNode(node);
        node->children[1]->aabb.SetCenterHalfSize(center + Vector3(+x_half, 0.0f, -z_half), scale);
        node->children[2] = CreateNode(node);
        node->children[2]->aabb.SetCenterHalfSize(center + Vector3(-x_half, 0.0f, +z_half), scale);
        node->children[3] = CreateNode(node);
        node->children[3]->aabb.SetCenterHalfSize(center + Vector3(-x_half, 0.0f, -z_half), scale);

        size_t size       = node->sub_terrain.faces.size();
        size_t child_size = size / 4 + (size_t)sqrtf((float)size);
        for (size_t j = 0; j < 4; ++j)
        {
            node->children[j]->sub_terrain.faces.reserve(child_size);
        }

        for (size_t i = 0; i < size; ++i)
        {
            for (size_t j = 0; j < 4; ++j)
            {
                if (node->children[j]->aabb.ContainsExceptY(node->sub_terrain.faces[i]))
                {
                    node->children[j]->sub_terrain.faces.push_back(node->sub_terrain.faces[i]);
                }
            }
        }

        node->sub_terrain.faces.clear();
        int next_height = height + 1;

        BuildTreeRecursive(node->children[0], next_height);
        BuildTreeRecursive(node->children[1], next_height);
        BuildTreeRecursive(node->children[2], next_height);
        BuildTreeRecursive(node->children[3], next_height);
    }

    SpaceNode* TerrainSpace::CreateNode(SpaceNode* parent)
    {
        SpaceNode* node = new SpaceNode();
        node->parent    = parent;
        m_nodes.push_back(node);
        return node;
    }
}
