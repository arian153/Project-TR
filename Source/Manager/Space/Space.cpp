/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#include "Space.hpp"
#include "../../System/Graphics/RenderSystem.hpp"
#include "../Object/ObjectManager.hpp"
#include "../Component/ComponentManager.hpp"
#include "../Resource/ResourceType/JsonResource.hpp"
#include "SpaceManager.hpp"
#include "../../System/Logic/LogicSystem.hpp"
#include "../../System/Logic/LogicSubsystem.hpp"

namespace GAM400
{
    Space::Space()
    {
    }

    Space::~Space()
    {
    }

    void Space::Initialize(eSubsystemFlag flag, RenderSystem* render_system, ObjectFactory* obj_factory, ComponentRegistry* cmp_registry, LogicSystem* logic_system)
    {
        m_creation_flag = flag;
        //create component manager
        if (m_component_manager == nullptr && HasFlag(flag, eSubsystemFlag::ComponentManager))
        {
            m_component_manager = new ComponentManager();
            m_component_manager->Initialize(cmp_registry, this);
        }
        //create object manager
        if (m_object_manager == nullptr && HasFlag(flag, eSubsystemFlag::ObjectManager))
        {
            m_object_manager = new ObjectManager();
            m_object_manager->Initialize(obj_factory, this);
        }
        //create scene
        if (m_scene == nullptr && HasFlag(flag, eSubsystemFlag::Scene))
        {
            m_scene = render_system->CreateScene();
            m_scene->Initialize();
        }
        //create logic
        if (m_logic_subsystem == nullptr && HasFlag(flag, eSubsystemFlag::Logic))
        {
            m_logic_subsystem = logic_system->CreateLogicSubsystem();
            m_logic_subsystem->Initialize();
            if (m_scene != nullptr)
            {
                m_logic_subsystem->SetPrimitiveRenderer(m_scene->GetPrimitiveRenderer());
            }
        }
    }

    void Space::Initialize(JsonResource* space_resource, RenderSystem* render_system, ObjectFactory* obj_factory, ComponentRegistry* cmp_registry, LogicSystem* logic_system)
    {
        m_space_resource = space_resource;
        space_resource->LoadSpaceFlag(this);
        //create component manager
        if (m_component_manager == nullptr && HasFlag(m_creation_flag, eSubsystemFlag::ComponentManager))
        {
            m_component_manager = new ComponentManager();
            m_component_manager->Initialize(cmp_registry, this);
        }
        //create object manager
        if (m_object_manager == nullptr && HasFlag(m_creation_flag, eSubsystemFlag::ObjectManager))
        {
            m_object_manager = new ObjectManager();
            m_object_manager->Initialize(obj_factory, this);
        }
        //create scene
        if (m_scene == nullptr && HasFlag(m_creation_flag, eSubsystemFlag::Scene))
        {
            m_scene = render_system->CreateScene();
            m_scene->Initialize();
        }
        //create logic
        if (m_logic_subsystem == nullptr && HasFlag(m_creation_flag, eSubsystemFlag::Logic))
        {
            m_logic_subsystem = logic_system->CreateLogicSubsystem();
            m_logic_subsystem->Initialize();
            if (m_scene != nullptr)
            {
                m_logic_subsystem->SetPrimitiveRenderer(m_scene->GetPrimitiveRenderer());
            }
        }
        space_resource->LoadData(this);
    }

    void Space::Shutdown(RenderSystem* render_system, LogicSystem* logic_system)
    {
        //maybe add a save data to file.
        //shutdown logic
        if (m_world != nullptr && HasFlag(m_creation_flag, eSubsystemFlag::Logic))
        {
            logic_system->RemoveLogicSubsystem(m_logic_subsystem);
        }
        //shutdown scene
        if (m_scene != nullptr && HasFlag(m_creation_flag, eSubsystemFlag::Scene))
        {
            render_system->RemoveScene(m_scene);
        }
        //shutdown object manager
        if (m_object_manager != nullptr && HasFlag(m_creation_flag, eSubsystemFlag::ObjectManager))
        {
            m_object_manager->Shutdown();
            delete m_object_manager;
            m_object_manager = nullptr;
        }
        //shutdown component manager
        if (m_component_manager != nullptr && HasFlag(m_creation_flag, eSubsystemFlag::ComponentManager))
        {
            m_component_manager->Shutdown();
            delete m_component_manager;
            m_component_manager = nullptr;
        }
    }

    void Space::Update(Real dt) const
    {
        if (m_logic_subsystem != nullptr)
        {
            m_logic_subsystem->Update(dt);
        }
        //update animation
        //update sound
        if (m_scene != nullptr)
        {
            m_scene->Update(dt);
        }
    }

    void Space::Update(Real dt, eSubsystemFlag flag) const
    {
        if (m_logic_subsystem != nullptr && HasFlag(flag, eSubsystemFlag::Logic))
        {
            m_logic_subsystem->Update(dt);
        }

        if (m_scene != nullptr && HasFlag(flag, eSubsystemFlag::Scene))
        {
            m_scene->Update(dt);
        }
    }

    void Space::Render() const
    {
        if (m_logic_subsystem != nullptr)
        {
            m_logic_subsystem->Render();
        }
        //update animation
        //update sound
        if (m_scene != nullptr)
        {
            m_scene->Render();
        }
    }

    void Space::UpdateSubsystem(Real dt, eSubsystemFlag flag) const
    {
        if (flag == eSubsystemFlag::Logic)
        {
            if (m_logic_subsystem != nullptr)
            {
                m_logic_subsystem->Update(dt);
            }
        }
        if (flag == eSubsystemFlag::Scene)
        {
            if (m_scene != nullptr)
            {
                m_scene->Update(dt);
            }
        }
    }

    void Space::RenderSubsystem(eSubsystemFlag flag) const
    {
        if (flag == eSubsystemFlag::Logic)
        {
            auto logic = GetLogicSubsystem();
            if (logic != nullptr)
            {
                logic->Render();
            }
        }
        if (flag == eSubsystemFlag::Scene)
        {
            auto scene = GetScene();
            if (scene != nullptr)
            {
                scene->Render();
            }
        }
    }

    void Space::ConnectSubsystem(ComponentManager* component_manager)
    {
        if (m_component_manager == nullptr && HasFlag(m_creation_flag, eSubsystemFlag::ComponentManager) == false)
        {
            m_component_manager = component_manager;
        }
    }

    void Space::ConnectSubsystem(ObjectManager* object_manager)
    {
        if (m_object_manager == nullptr && HasFlag(m_creation_flag, eSubsystemFlag::ObjectManager) == false)
        {
            m_object_manager = object_manager;
        }
    }

    void Space::ConnectSubsystem(Scene* scene)
    {
        if (m_scene == nullptr && HasFlag(m_creation_flag, eSubsystemFlag::Scene) == false)
        {
            m_scene = scene;
        }
    }

    void Space::ConnectSubsystem(World* world)
    {
        if (m_world == nullptr && HasFlag(m_creation_flag, eSubsystemFlag::World) == false)
        {
            m_world = world;
        }
    }

    void Space::ConnectSubsystem(LogicSubsystem* logic_system)
    {
        if (m_logic_subsystem == nullptr && HasFlag(m_creation_flag, eSubsystemFlag::Logic) == false)
        {
            m_logic_subsystem = logic_system;
        }
    }

    ObjectManager* Space::GetObjectManager() const
    {
        return m_object_manager;
    }

    ComponentManager* Space::GetComponentManager() const
    {
        return m_component_manager;
    }

    ResourceManager* Space::GetResourceManager() const
    {
        return m_resource_manager;
    }

    Scene* Space::GetScene() const
    {
        return m_scene;
    }

    World* Space::GetWorld() const
    {
        return m_world;
    }

    LogicSubsystem* Space::GetLogicSubsystem() const
    {
        return m_logic_subsystem;
    }

    Application* Space::GetApplication() const
    {
        return m_space_manager->GetApplication();
    }

    bool Space::IsSubsystemUpdate(eSubsystemFlag flag) const
    {
        return HasFlag(m_update_flag, flag);
    }

    bool Space::IsSubsystemFixedUpdate(eSubsystemFlag flag) const
    {
        return HasFlag(m_fixed_update_flag, flag);
    }

    bool Space::IsActivated() const
    {
        return m_b_activate;
    }

    std::string Space::GetName() const
    {
        return m_name;
    }
}
