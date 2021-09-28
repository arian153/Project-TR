#include "Terrain.hpp"

#include "../Common/Buffer2/IndexBufferCommon.hpp"
#include "../Common/Buffer2/VertexBufferCommon.hpp"

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
}
