#include "TerrainComponent.hpp"

namespace GAM400
{
    TerrainComponent::~TerrainComponent()
    {
    }

    void TerrainComponent::Initialize()
    {
    }

    void TerrainComponent::Update(Real dt)
    {
    }

    void TerrainComponent::Shutdown()
    {
    }

    bool TerrainComponent::Load(const Json::Value& data)
    {
        return true;
    }

    void TerrainComponent::Save(Json::Value& data) const
    {
    }

    void TerrainComponent::Edit(CommandRegistry* command_registry)
    {
    }

    void TerrainComponent::Subscribe()
    {
    }

    void TerrainComponent::Unsubscribe()
    {
    }

    TerrainComponent::TerrainComponent(Object* owner)
        : Component(owner)
    {
    }

    void TerrainComponent::Clone(TerrainComponent* origin)
    {
    }
}
