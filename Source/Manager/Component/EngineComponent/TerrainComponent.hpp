#pragma once

#include <vector>

#include "..//Component.hpp"
#include "../../../System/Graphics/DataType/MaterialData.hpp"
#include "../../../System/Graphics/DataType/MeshData.hpp"
#include "../../../System/Math/Primitive/ConvexHull3D/Box.hpp"
#include "../../../System/Math/Primitive/ConvexHull3D/Sphere.hpp"
#include "../../../System/Math/Utility/VectorDef.hpp"

namespace GAM400
{
    struct EditGridI32;
    struct EditGridReal;
    class TextResource;

    class TerrainComponent final : public Component
    {
    public:
        ~TerrainComponent();
        TerrainComponent()                                       = delete;
        TerrainComponent(const TerrainComponent& rhs)            = delete;
        TerrainComponent& operator=(const TerrainComponent& rhs) = delete;

        void Initialize() override;
        void Update(Real dt) override;
        void Shutdown() override;

    protected:
        bool Load(const Json::Value& data) override;
        void Save(Json::Value& data) const override;
        void Edit(CommandRegistry* command_registry) override;
        void Subscribe() override;
        void Unsubscribe() override;

    private:
        friend class TerrainFactory;
        friend class Terrain;

    private:
        explicit TerrainComponent(Object* owner);
        void     Clone(TerrainComponent* origin);

        void SetTerrainSeed(const EditGridI32& data);

    private:
        Terrain*           m_terrain = nullptr;
        MaterialIdentifier m_material_identifier;
        MaterialColor      m_material_color;
        MeshData           m_edit_grid;

        Real m_edit_width, m_edit_depth;
        I32  m_edit_w_lod, m_edit_d_lod;

        Real m_edit_tri_a, m_edit_tri_b;
        Real m_edit_per_s, m_edit_per_d;

        U32  m_edit_seed = 142356;
        Real m_edit_hm_scale;

        std::vector<TextResource*> m_height_maps;
        std::vector<std::string>   m_height_map_names;
        int                        m_height_map_idx = -1;

        U32 m_noise_seed = 142356;

        int m_terrain_mode = 2;

        int m_w_idx = 0;
        int m_d_idx = 0;

        Vector3 m_picking_point;
        Vector3 m_closest_point;
        Sphere  m_drawing_sphere;
        Box     m_drawing_box;

        U32 m_face_a = 0;
        U32 m_face_b = 0;
        U32 m_face_c = 0;
    };
}
