#pragma once
#include "../DataType/MeshData.hpp"

namespace GAM400
{
    class VertexBufferCommon;
    class IndexBufferCommon;

    class Terrain
    {
    public:
        Terrain();
        ~Terrain();

        void Bind();

        void CreateBuffer();
        void ReleaseBuffer();

        void Build();

        Real GenerateTrigonometricHeight(Real x, Real z) const;
        Vector3 GenerateTrigonometricNormal(Real x, Real z) const;

        void ClearGrid();

    private:
        Real m_terrain_width = 200.0f;
        Real m_terrain_depth = 200.0f;
        size_t m_terrain_vertex_size = 0;
        

        Real m_trigonometric_factor_a = 0.3f;
        Real m_trigonometric_factor_b = 0.1f;

        MeshData            m_grid;
        VertexBufferCommon* m_vertex_buffer = nullptr;
        IndexBufferCommon*  m_index_buffer  = nullptr;
    };
}
