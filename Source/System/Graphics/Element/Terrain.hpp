#pragma once
#include "../Common/Texture/TextureArrayCommon.hpp"
#include "../DataType/MaterialData.hpp"
#include "../DataType/MeshData.hpp"

namespace GAM400
{
    struct MaterialIdentifier;
    class ConstantBufferCommon;
    class RendererCommon;
    class TerrainComponent;
    class VertexBufferCommon;
    class IndexBufferCommon;

    class Terrain
    {
    public:
        Terrain();
        ~Terrain();

        void Initialize();
        void Update(Real dt);
        void Shutdown();
        void Bind() const;
        void Draw() const;

        void CreateBuffer();
        void ReleaseBuffer();
        void BuildBuffer() const;

        void    GenerateTrigonometric();
        Real    GenerateTrigonometricHeight(Real x, Real z) const;
        Vector3 GenerateTrigonometricNormal(Real x, Real z) const;

        void ClearGrid();

        void AddTexture(TextureCommon* texture);
        void ClearTexture();
        void RemoveTexture(TextureCommon* texture);
        void SetRenderer(RendererCommon* renderer);
        void SetMaterialIdentifier(const MaterialIdentifier& material_data);

    private:
        friend class TerrainComponent;

    private:
        Real   m_terrain_width       = 200.0f;
        Real   m_terrain_depth       = 200.0f;
        U32    m_width_div           = 50;
        U32    m_depth_div           = 50;
        size_t m_terrain_vertex_size = 0;

        Real m_trigonometric_factor_a = 0.3f;
        Real m_trigonometric_factor_b = 0.1f;

        MeshData              m_grid;
        TextureArrayCommon    m_textures;
        MaterialIdentifier    m_material;
        RendererCommon*       m_renderer       = nullptr;
        VertexBufferCommon*   m_vertex_buffer  = nullptr;
        IndexBufferCommon*    m_index_buffer   = nullptr;
        TerrainComponent*     m_component      = nullptr;
        ConstantBufferCommon* m_texture_buffer = nullptr;
    };
}
