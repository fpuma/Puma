#pragma once

#include <engine/services/base/iservice.h>
#include <pina.h>

namespace puma
{
    class EcsService final : public IService
    {
    public:

        EcsService() {}

        virtual ~EcsService() {}

        pina::ECS* get() { return &m_ecs; };

    private:

        pina::ECS m_ecs;

    };
}

#include <engine/services/base/iservicecontainer.h>

#define gECS puma::DefaultServices::getInstance()->get<puma::EcsService>()->get()
#define gEntities puma::DefaultServices::getInstance()->get<puma::EcsService>()->get()->getEntityProvider()
#define gComponents puma::DefaultServices::getInstance()->get<puma::EcsService>()->get()->getComponentProvider()