#include "Terrain.hpp"

#include "../Common/Buffer2/IndexBufferCommon.hpp"
#include "../Common/Buffer2/VertexBufferCommon.hpp"
#include "../DataType/MeshData.hpp"
#include "../Utility/MeshGenerator.hpp"

namespace GAM400
{
    Terrain::Terrain()
    {
    }

    Terrain::~Terrain()
    {
    }

    void Terrain::Bind()
    {
    }

    void Terrain::CreateBuffer()
    {
        if (m_index_buffer == nullptr)
        {
            m_index_buffer = new IndexBufferCommon();
        }

        if (m_vertex_buffer == nullptr)
        {
            m_vertex_buffer = new VertexBufferCommon();
        }
    }

    void Terrain::ReleaseBuffer()
    {
        if (m_index_buffer != nullptr)
        {
            m_index_buffer->Shutdown();
            delete m_index_buffer;
            m_index_buffer = nullptr;
        }

        if (m_vertex_buffer != nullptr)
        {
            m_vertex_buffer->Shutdown();
            delete m_vertex_buffer;
            m_vertex_buffer = nullptr;
        }
    }

    void Terrain::Build()
    {
        size_t size = m_grid.vertices.size();

        for (size_t i = 0; i < size; ++i)
        {
            Vector3 p = m_grid.vertices[i].GetPosition();
            p.y       = GenerateTrigonometricHeight(p.x, p.z);

            m_grid.vertices[i].SetPosition(p);
            m_grid.vertices[i].SetNormal(GenerateTrigonometricNormal(p.x, p.y));
            m_grid.vertices[i].CalculateTangentAndBinormal();
        }

        if (m_terrain_vertex_size == size)
        {
            //use dynamic buffer
        }
        else
        {
            //resize vertex & index buffer
        }
    }

    Real Terrain::GenerateTrigonometricHeight(Real x, Real z) const
    {
        return m_trigonometric_factor_a * (z * sinf(m_trigonometric_factor_b * x) + x * cosf(m_trigonometric_factor_b * z));
    }

    Vector3 Terrain::GenerateTrigonometricNormal(Real x, Real z) const
    {
        Real ab = m_trigonometric_factor_a * m_trigonometric_factor_b;

        Vector3 normal(
                       -ab * z * cosf(m_trigonometric_factor_b * x) - m_trigonometric_factor_a * cosf(m_trigonometric_factor_b * z),
                       1.0f,
                       -m_trigonometric_factor_a * sinf(m_trigonometric_factor_b * x) + ab * x * sinf(m_trigonometric_factor_b * z));

        return normal.Unit();
    }

    void Terrain::ClearGrid()
    {
        MeshGenerator mesh_generator;
        mesh_generator.CreateGrid(m_terrain_width, m_terrain_depth, 50, 50, m_grid);
        m_terrain_vertex_size = m_grid.vertices.size();
    }
}
