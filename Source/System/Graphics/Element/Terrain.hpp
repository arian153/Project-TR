#pragma once

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

    private:

        VertexBufferCommon* m_vertex_buffer = nullptr;
        IndexBufferCommon*  m_index_buffer  = nullptr;
    };
}
