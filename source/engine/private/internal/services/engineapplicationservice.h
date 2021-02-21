#pragma once

#include <engine/services/iengineapplicationservice.h>
#include <internal/application/engineapplication.h>

namespace puma
{
    class EngineApplicationService : public IEngineApplicationService
    {
    public:

        EngineApplicationService() { m_engineApplication = std::make_unique<EngineApplication>(); }

        ~EngineApplicationService() { m_engineApplication.reset(); }

        EngineApplication* get() override { return m_engineApplication.get(); }

    private:

        std::unique_ptr<EngineApplication> m_engineApplication;
    };
}

#include <engine/services/base/iservicecontainer.h>

#define gInternalEngineApplication puma::DefaultServices::getInstance()->get<puma::EngineApplicationService>()->get()