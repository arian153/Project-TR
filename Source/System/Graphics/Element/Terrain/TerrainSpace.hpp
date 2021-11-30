#pragma once
#include <vector>

#include "SubTerrain.hpp"
#include "../../../Math/Algebra/Vector3.hpp"

namespace GAM400
{
    class Terrain;
    class PrimitiveRenderer;
    class Ray;
    class SpaceNode;
    class HitData;

    class TerrainAABB
    {
    public:
        TerrainAABB();
        explicit TerrainAABB(SpaceNode* node);
        ~TerrainAABB();
        void SetMinMax(const Vector3& min, const Vector3& max);
        void SetCenterHalfSize(const Vector3& center, const Vector3& half_size);

        bool Intersect(TerrainAABB* aabb) const;
        bool Intersect(const TerrainAABB& aabb) const;
        bool Contains(const Vector3& point) const;
        bool ContainsExceptY(const Vector3& point) const;
        bool ContainsExceptY(const Vector3& p0, const Vector3& p1, const Vector3& p2) const;
        bool ContainsExceptY(const TerrainFace& face) const;
        bool Contains(TerrainAABB* aabb) const;
        bool Contains(const TerrainAABB& aabb) const;
        bool TestRayIntersection(const Ray& ray, Real& t, Real max_distance = -1.0f) const;

        void ResetMinMaxY();
        void SetMinMaxY(Real min, Real max);
        void ExpandY(Real min, Real max);

        Real    Volume() const;
        Vector3 Center() const;
        Vector3 Size() const;
        Vector3 HalfSize() const;
        Vector3 Min() const;
        Vector3 Max() const;

        TerrainAABB Union(const TerrainAABB& aabb) const;
    

        SpaceNode* GetSpaceNode() const;
    private:
        Vector3    m_min, m_max;
        SpaceNode* m_node = nullptr;
    };

    class SpaceNode
    {
    public:
        SpaceNode();
        ~SpaceNode();

        bool IsLeaf() const;
    public:
        SpaceNode*  parent = nullptr;
        SpaceNode*  children[4]; //4 child node
        TerrainAABB aabb;
        SubTerrain  sub_terrain;
    };

    class TerrainSpace
    {
    public:
        TerrainSpace();
        ~TerrainSpace();

        void Initialize(Terrain* terrain);
        void Update();
        void UpdateAABBNode(SpaceNode* leaf_node) const;
        void Shutdown();
        void Render(PrimitiveRenderer* primitive_renderer);

        SubTerrain* Pick(const Vector3& point) const;

        void Query(const TerrainAABB& aabb, std::vector<SubTerrain*>& output_terrain, std::vector<TerrainFace*>& output_faces) const;
        void CastRay(HitData& result, Real max_distance = -1.0f) const;

        Real RootMinY() const;
        Real RootMaxY() const;
        Real RootScaleY() const;

    private:
        void BuildTreeRecursive(SpaceNode* node, int height);

        SpaceNode* CreateNode(SpaceNode* parent);

    private:
        Terrain*   m_terrain        = nullptr;
        SpaceNode* m_root           = nullptr;
        Real       m_cell_width     = 100.0f;
        Real       m_cell_depth     = 100.0f;
        int        m_tree_height    = 0;
        Real       m_size_threshold = 500.0f;

        std::vector<SpaceNode*> m_nodes;
        std::vector<SpaceNode*> m_leaves;
    };
}
