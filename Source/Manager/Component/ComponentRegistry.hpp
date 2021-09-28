#pragma once
#include <string>
#include <list>
#include <unordered_map>

namespace GAM400
{
    class ComponentFactory;

    class ComponentRegistry
    {
    public:
        ComponentRegistry();
        ~ComponentRegistry();

        bool Initialize();
        bool Shutdown();
        bool AddFactory(ComponentFactory* factory);

    private:
        std::unordered_map<std::string, ComponentFactory*> m_factories;
        std::list<std::string>                             m_keys;

        friend class ComponentManager;

    private:
    };
}
