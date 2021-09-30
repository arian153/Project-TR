#include "Terrain.hpp"

#include "../../Core/Utility/CoreUtility.hpp"
#include "../Common/Buffer2/ConstantBufferCommon.hpp"
#include "../Common/Buffer2/ConstantBufferData.hpp"
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

    void Terrain::Initialize()
    {
        CreateBuffer();
    }

    void Terrain::Update(Real dt)
    {
        E5_UNUSED_PARAM(dt);
    }

    void Terrain::Shutdown()
    {
        ReleaseBuffer();
    }

    void Terrain::Bind() const
    {
        m_vertex_buffer->Bind(0);
        m_index_buffer->Bind(0);
        m_textures.Bind();
        m_texture_buffer->Bind();
    }

    void Terrain::Draw() const
    {
        m_index_buffer->Draw();
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

        if (m_texture_buffer == nullptr)
        {
            m_texture_buffer = new ConstantBufferCommon();
            m_texture_buffer->Init(m_renderer, eBindingStage::PixelShader, sizeof(TextureBufferData), 0);
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

        if (m_texture_buffer != nullptr)
        {
            m_texture_buffer->Shutdown();
            delete m_texture_buffer;
            m_texture_buffer = nullptr;
        }
    }

    void Terrain::BuildBuffer() const
    {
        size_t size = m_grid.vertices.size();
        if (m_terrain_vertex_size == size)
        {
            //update vertex buffer
            m_vertex_buffer->Update(m_grid.vertices);
        }
        else
        {
            //resize vertex & index buffer
            m_index_buffer->Shutdown();
            m_vertex_buffer->Shutdown();
            m_index_buffer->Init(m_renderer, m_grid.indices);
            m_vertex_buffer->Init(m_renderer, m_grid.vertices, true);
        }
    }

    void Terrain::GenerateTrigonometric()
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
        mesh_generator.CreateGrid(m_terrain_width, m_terrain_depth, m_depth_div, m_width_div, m_grid);
        m_terrain_vertex_size = m_grid.vertices.size();
    }

    void Terrain::AddTexture(TextureCommon* texture)
    {
        m_textures.PushBack(texture);
    }

    void Terrain::ClearTexture()
    {
        m_textures.Clear();
    }

    void Terrain::RemoveTexture(TextureCommon* texture)
    {
        m_textures.Erase(texture);
    }

    void Terrain::SetRenderer(RendererCommon* renderer)
    {
        m_renderer = renderer;
    }

    void Terrain::SetMaterialIdentifier(const MaterialIdentifier& material_data)
    {
        m_material = material_data;
        m_textures.Clear();

        //get actual resource data from resource manager.
        if (m_texture_buffer != nullptr)
        {
            TextureBufferData data;
            data.diff_type = m_material.diffuse_type;
            data.spec_type = m_material.specular_type;
            data.norm_type = m_material.normal_type;
            //E5_TODO : need to update user gamma setting
            data.gamma = 2.2f;

            m_texture_buffer->Update(data);
        }
    }
}
