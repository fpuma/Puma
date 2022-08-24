#pragma once

#include <modules/pina/componentprovider.h>
#include <modules/pina/entityprovider.h>
#include <modules/pina/systemprovider.h>
#include <pina/ecs.h>

namespace puma
{
    class ECS
    {
    public:

        ECS()
        {
            m_ecs.initEntities();
            m_ecs.initComponents();
            m_ecs.initSystems<SystemProvider>();
        }

        EntityProvider* getEntityProvider()         { return static_cast<EntityProvider*>(m_ecs.getEntityProvider()); }
        ComponentProvider* getComponentProvider()   { return static_cast<ComponentProvider*>(m_ecs.getComponentProvider()); }
        SystemProvider* getSystemProvider()         { return static_cast<SystemProvider*>(m_ecs.getSystemProvider()); }

        const EntityProvider* getEntityProvider() const         { return static_cast<const EntityProvider*>(m_ecs.getEntityProvider()); }
        const ComponentProvider* getComponentProvider() const   { return static_cast<const ComponentProvider*>(m_ecs.getComponentProvider()); }
        const SystemProvider* getSystemProvider() const         { return static_cast<const SystemProvider*>(m_ecs.getSystemProvider()); }

    private:
        
        pina::ECS m_ecs;
    };
    
}