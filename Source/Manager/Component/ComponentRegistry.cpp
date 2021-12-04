/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include "ComponentRegistry.hpp"
#include "ComponentFactory.hpp"

//factories
#include "EngineFactory/CameraFactory.hpp"
#include "EngineFactory/TransformFactory.hpp"
#include "EngineFactory/MeshFactory.hpp"
#include "EngineFactory/LightFactory.hpp"
#include "EngineFactory/ParticleEmitterFactory.hpp"
#include "EngineFactory/SkyFactory.hpp"
#include "EngineFactory/TerrainFactory.hpp"

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
        AddFactory(new TerrainFactory());
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
