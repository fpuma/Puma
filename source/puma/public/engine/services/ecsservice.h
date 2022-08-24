#pragma once

#include <engine/services/base/iservice.h>
#include <modules/pina/ecs.h>

namespace puma
{
    class EcsService : public IService
    {
    public:

        EcsService() 
            :m_ecs( std::make_unique<ECS>() )
        {}

        virtual ~EcsService() { m_ecs.reset(); }

        ECS* get() { return m_ecs.get(); };

    private:

        std::unique_ptr<ECS> m_ecs;

    };
}

#include <engine/services/base/iservicecontainer.h>

#define gEntities puma::DefaultServices::getInstance()->get<puma::EcsService>()->get()->getEntityProvider()
#define gComponents puma::DefaultServices::getInstance()->get<puma::EcsService>()->get()->getComponentProvider()
#define gSystems puma::DefaultServices::getInstance()->get<puma::EcsService>()->get()->getSystemProvider()