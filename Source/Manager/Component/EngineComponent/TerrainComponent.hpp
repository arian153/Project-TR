#pragma once

#include <vector>

#include "..//Component.hpp"
#include "../../../System/Graphics/DataType/MaterialData.hpp"
#include "../../../System/Math/Primitive/ConvexHull3D/Sphere.hpp"
#include "../../../System/Math/Utility/VectorDef.hpp"

namespace GAM400
{
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

    private:
        Terrain*           m_terrain = nullptr;
        MaterialIdentifier m_material_identifier;
        MaterialColor      m_material_color;

        std::vector<TextResource*> m_height_maps;
        std::vector<std::string>   m_height_map_names;
        int                        m_height_map_idx;

        U32 m_noise_seed   = 142356;
        int m_terrain_mode = 2;

        int m_w_idx = 0;
        int m_d_idx = 0;

        Vector3 m_picking_point;
        Vector3 m_closest_point;
        Sphere  m_drawing_sphere;

        U32 m_face_a = 0;
        U32 m_face_b = 0;
        U32 m_face_c = 0;
    };
}
