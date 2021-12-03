#pragma once
#include "../../Math/Algebra/Matrix44.hpp"
#include "../../Math/Primitive/ConvexHull3D/Sphere.hpp"
#include "../../Math/Utility/NoiseUtility.hpp"
#include "../Common/Texture/TextureArrayCommon.hpp"
#include "../DataType/MaterialData.hpp"
#include "../DataType/MeshData.hpp"
#include "Terrain/HitData.hpp"
#include "Terrain/TerrainSpace.hpp"

namespace GAM400
{
    class Transform;
    class InputCommon;
    class Matrix44;
    struct MaterialIdentifier;
    class ConstantBufferCommon;
    class RendererCommon;
    class TerrainComponent;
    class VertexBufferCommon;
    class IndexBufferCommon;

    struct EditGridReal
    {
        explicit EditGridReal(const MeshData& data)
            : grid(data)
        {
        }

        MeshData grid;
        Real     value = 0.0f;
    };

    struct EditGridI32
    {
        explicit EditGridI32(const MeshData& data)
            : grid(data)
        {
        }

        MeshData grid;
        I32      value = 0;
    };

    struct EditGridBool
    {
        explicit EditGridBool(const MeshData& data)
            : grid(data)
        {
        }

        MeshData grid;
        bool     boolean = false;
    };

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

        void IsMousePressed(const Ray& ray);
        void IsMouseDown(const Ray& ray);
        void UpdatePicking(const Ray& ray);

        void CreateBuffer();
        void ReleaseBuffer();
        void BuildBuffer(bool update_space = true);

        void ExportPPM();
        void ExportOBJ();

        void    GenerateTrigonometric();
        Real    GenerateTrigonometricHeight(Real x, Real z) const;
        Vector3 GenerateTrigonometricNormal(Real x, Real z) const;

        void ClearGrid();

        void GeneratePerlinNoise();

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
        void CalculateNTB(U32 idx);
        void CalculateNTB(const TerrainFace& face);

        void SetMaterialAmbient(const Color& color);
        void SetMaterialDiffuse(const Color& color);
        void SetMaterialSpecular(const Color& color);

        void SetGridData(const MeshData& grid_data);
        void SetTerrainWidth(const EditGridReal& width);
        void SetTerrainDepth(const EditGridReal& depth);
        void SetTerrainWidthLOD(const EditGridI32& w_lod);
        void SetTerrainDepthLOD(const EditGridI32& d_lod);

        void SetTerrainTriA(const EditGridReal& data);
        void SetTerrainTriB(const EditGridReal& data);
        void SetTerrainPerS(const EditGridReal& data);
        void SetTerrainPerD(const EditGridReal& data);

        void SetTerrainHMS(const EditGridReal& data);

    private:
        friend class TerrainComponent;
        friend class TerrainSpace;

    private:
        Real   m_terrain_width       = 400.0f;
        Real   m_terrain_depth       = 400.0f;
        I32    m_width_div           = 200;
        I32    m_depth_div           = 200;
        size_t m_terrain_vertex_size = 0;
        int    m_smooth_level        = 2;

        int         m_brush_mode = 0;
        TerrainAABB m_brush;
        Vector3     m_brush_size;
        Real        m_brush_intensity = 0.01f;

        Real m_trigonometric_factor_a = 0.3f;
        Real m_trigonometric_factor_b = 0.05f;
        Real m_perlin_noise_scale     = 100.0f;
        Real m_perlin_noise_density   = 100.0f;
        bool m_b_noise_user_random    = true;
        bool m_b_analytical_normal    = false;
        bool m_b_edit_down            = false;

        Real m_height_map_scale = 100.0f;

        Matrix44 m_world;

        PerlinNoise                     m_noise_utility;
        MeshData                        m_grid;
        TerrainSpace                    m_terrain_space;
        std::vector<GeometryPointIndex> m_point_indices;

        HitData m_edit_hit_data;
        int     m_hit_mouse_y = 0;
        Vector3 m_hit_vertex;

        TextureArrayCommon  m_textures;
        MaterialIdentifier  m_material;
        MaterialColor       m_mat_color;
        RendererCommon*     m_renderer      = nullptr;
        InputCommon*        m_input         = nullptr;
        VertexBufferCommon* m_vertex_buffer = nullptr;
        IndexBufferCommon*  m_index_buffer  = nullptr;
        TerrainComponent*   m_component     = nullptr;
        Transform*          m_transform     = nullptr;

        TextureCommon* m_height_map_texture         = nullptr;
        bool           m_height_map_texture_created = false;

        ConstantBufferCommon* m_matrix_buffer   = nullptr;
        ConstantBufferCommon* m_texture_buffer  = nullptr;
        ConstantBufferCommon* m_material_buffer = nullptr;
    };
}
