#pragma once
#include "../../Math/Algebra/Matrix44.hpp"
#include "../../Math/Utility/NoiseUtility.hpp"
#include "../Common/Texture/TextureArrayCommon.hpp"
#include "../DataType/MaterialData.hpp"
#include "../DataType/MeshData.hpp"
#include "Terrain/TerrainSpace.hpp"

namespace GAM400
{
    class Matrix44;
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
        void BuildBuffer();

        void    GenerateTrigonometric();
        Real    GenerateTrigonometricHeight(Real x, Real z) const;
        Vector3 GenerateTrigonometricNormal(Real x, Real z) const;

        void ClearGrid();

        void GeneratePerlinNoise();
        void AddPerlinNoise();

        void AddTexture(TextureCommon* texture);
        void ClearTexture();
        void RemoveTexture(TextureCommon* texture);
        void SetRenderer(RendererCommon* renderer);
        void SetMaterialIdentifier(const MaterialIdentifier& material_data);
        void SetMaterialColor(const MaterialColor& color_data);

        void SetWorldMatrix(const Matrix44& world);
        void UpdateMatrixBuffer(const Matrix44& view, const Matrix44& proj) const;
        void UpdateMaterialBuffer() const;
        void UpdateTextureBuffer() const;

        std::string GetShaderType() const;

        void CalculateNTB();
        void CalculateGridIndices();
        void SetNoiseSeed(U32 seed);

    private:
        friend class TerrainComponent;
        friend class TerrainSpace;

    private:
        Real   m_terrain_width       = 400.0f;
        Real   m_terrain_depth       = 400.0f;
        I32    m_width_div           = 400;
        I32    m_depth_div           = 400;
        size_t m_terrain_vertex_size = 0;
        int    m_smooth_level        = 2;

        Real m_trigonometric_factor_a = 0.3f;
        Real m_trigonometric_factor_b = 0.05f;
        Real m_perlin_noise_scale     = 100.0f;
        Real m_perlin_noise_density   = 100.0f;
        bool m_b_noise_user_random    = true;

        Real m_height_map_scale = 100.0f;

        Matrix44 m_world;

        PerlinNoise                     m_noise_utility;
        MeshData                        m_grid;
        TerrainSpace                    m_space;
        std::vector<GeometryPointIndex> m_point_indices;

        TextureArrayCommon  m_textures;
        MaterialIdentifier  m_material;
        MaterialColor       m_mat_color;
        RendererCommon*     m_renderer      = nullptr;
        VertexBufferCommon* m_vertex_buffer = nullptr;
        IndexBufferCommon*  m_index_buffer  = nullptr;
        TerrainComponent*   m_component     = nullptr;

        ConstantBufferCommon* m_matrix_buffer   = nullptr;
        ConstantBufferCommon* m_texture_buffer  = nullptr;
        ConstantBufferCommon* m_material_buffer = nullptr;
    };
}
