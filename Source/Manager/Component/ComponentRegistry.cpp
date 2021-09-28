#include "ComponentRegistry.hpp"
#include "ComponentFactory.hpp"

//factories
#include "EngineFactory/CameraFactory.hpp"
#include "EngineFactory/TransformFactory.hpp"
#include "EngineFactory/MeshFactory.hpp"
#include "EngineFactory/LightFactory.hpp"
#include "EngineFactory/ParticleEmitterFactory.hpp"
#include "EngineFactory/SkyFactory.hpp"

namespace GAM400
{
    ComponentRegistry::ComponentRegistry()
    {
    }

    ComponentRegistry::~ComponentRegistry()
    {
    }

    bool ComponentRegistry::Initialize()
    {
        AddFactory(new TransformFactory());
        AddFactory(new CameraFactory());
        AddFactory(new MeshFactory());
        AddFactory(new LightFactory());
        AddFactory(new ParticleEmitterFactory());
        AddFactory(new SkyFactory());
        return true;
    }

    bool ComponentRegistry::Shutdown()
    {
        for (auto it = m_factories.begin(); it != m_factories.end(); ++it)
        {
            delete it->second;
            it->second = nullptr;
        }
        m_keys.clear();
        m_factories.clear();
        return true;
    }

    bool ComponentRegistry::AddFactory(ComponentFactory* factory)
    {
        if (factory != nullptr)
        {
            if (m_factories.find(factory->type) == m_factories.end())
            {
                m_keys.push_back(factory->type);
                m_factories.emplace(factory->type, factory);
                return true;
            }
        }
        return false;
    }
}
