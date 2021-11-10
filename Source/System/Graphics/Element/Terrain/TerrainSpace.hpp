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

    class TerrainAABB
    {
    public:
        TerrainAABB();
        ~TerrainAABB();
        void Set(const Vector3& min, const Vector3& max);

        bool Intersect(TerrainAABB* aabb) const;
        bool Intersect(const TerrainAABB& aabb) const;
        bool Contains(const Vector3& point) const;
        bool Contains(TerrainAABB* aabb) const;
        bool Contains(const TerrainAABB& aabb) const;
        bool TestRayIntersection(const Ray& ray, Real& t, Real max_distance = -1.0f) const;

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

    private:
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

        void Initialize();
        void Update(Real dt);
        void Shutdown();
        void Clear();
        void Release();
        void Render(PrimitiveRenderer* primitive_renderer);

        SubTerrain* Pick(const Vector3& point) const;

        void Query(const TerrainAABB& aabb, std::vector<SubTerrain*>& output) const;
        //void CastRay(RayCastResult& result, Real max_distance = -1.0f) const;

    private:
        Terrain*   m_terrain        = nullptr;
        SpaceNode* m_root           = nullptr;
        Real       m_cell_width     = 100.0f;
        Real       m_cell_depth     = 100.0f;
        int        m_tree_height    = 0;
        Real       m_size_threshold = 20.0f;
    };
}
