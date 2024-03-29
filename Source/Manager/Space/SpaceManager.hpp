/*---------------------------------------------------------------------
//All content (C) 2021 DigiPen (USA) Corporation, all rights reserved
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
Author: Eric Han
E-Mail: jangseok.han@digipen.edu
Language: C++, std::c++17
Platform: Visual Studio 2019 (v142), Windows SDK 10.0 x64>
-----------------------------------------------------------------------*/

#pragma once
#include "SubsystemFlag.hpp"
#include <vector>

namespace GAM400
{
    class Level;
    class LogicSystem;
    class ResourceManager;
    class JsonResource;
    class Space;
    class ObjectFactory;
    class ComponentRegistry;
    class PhysicsSystem;
    class RenderSystem;
    class Application;

    class SpaceManager
    {
    public:
        SpaceManager() = delete;
        explicit SpaceManager(
            RenderSystem*      render_system,
            ObjectFactory*     object_factory,
            ComponentRegistry* component_registry,
            ResourceManager*   resource_manager,
            LogicSystem*       logic_system);
        ~SpaceManager();

        void Initialize();
        void Shutdown();

        Space* GetGlobalSpace() const;
        Space* CreateSpace(Level* level, eSubsystemFlag flag);
        Space* CreateSpace(Level* level, JsonResource* resource);
        Space* CreateSpace(JsonResource* resource);
        void   RemoveSpace(Space* space);
        void   LoadSpace(Space* space, JsonResource* resource) const;

        void SetApplication(Application* app);

        Application* GetApplication() const;

    private:
        friend class Space;
        friend class SpaceEditor;

    private:
        eSubsystemFlag m_global_flag = eSubsystemFlag::None;

        Space*              m_global_space    = nullptr;
        Space*              m_archetype_space = nullptr;
        std::vector<Space*> m_spaces;
        //std::vector<Space*> m_active_spaces;

        PhysicsSystem*   m_physics_system   = nullptr;
        RenderSystem*    m_render_system    = nullptr;
        LogicSystem*     m_logic_system     = nullptr;
        ResourceManager* m_resource_manager = nullptr;

        //factory
        ObjectFactory*     m_object_factory     = nullptr;
        ComponentRegistry* m_component_registry = nullptr;


        Application* m_application = nullptr;
    };
}
