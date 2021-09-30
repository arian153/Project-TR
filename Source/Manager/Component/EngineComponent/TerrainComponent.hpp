#pragma once

#include "..//Component.hpp"
#include "../../../System/Math/Utility/VectorDef.hpp"

namespace GAM400
{
    class TerrainComponent final : public Component
    {
    public:
        ~TerrainComponent();
        TerrainComponent() = delete;
        TerrainComponent(const TerrainComponent& rhs) = delete;
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

    private:
        explicit TerrainComponent(Object* owner);
        void     Clone(TerrainComponent* origin);


    private:
    };
}
