#pragma once

#include <engine/services/isystemsservice.h>
#include <internal/ecs/base/containers/systemcontainer.h>

namespace puma
{
    class SystemsService final : public ISystemsService
    {
    public:

        SystemsService() { m_systems = std::make_unique<SystemContainer>(); }

        ~SystemsService() { m_systems.reset(); }

        SystemContainer* get() override { return m_systems.get(); }

        void uninit() { m_systems->uninit(); }

    private:

        std::unique_ptr<SystemContainer> m_systems;
    };
}

#include <engine/services/base/iservicecontainer.h>

#define gInternalSystems puma::DefaultServices::getInstance()->get<puma::SystemsService>()->get()