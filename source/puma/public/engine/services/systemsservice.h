#pragma once

#include <engine/services/base/iservice.h>
#include <engine/ecs/systems/base/systemprovider.h>

namespace puma
{
    class SystemsService final : public IService
    {
    public:

        SystemsService() {}

        virtual ~SystemsService() {}

        SystemProvider* get() { return &m_systemProvider; };

    private:

        SystemProvider m_systemProvider;

    };
}

#include <engine/services/base/iservicecontainer.h>

#define gSystems puma::DefaultServices::getInstance()->get<puma::SystemsService>()->get()