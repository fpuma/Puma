#pragma once

#include <engine/services/iengineapplicationservice.h>
#include <internal/application/engineapplication.h>

namespace puma
{
    class EngineApplicationService : public IEngineApplicationService
    {
    public:

        void uninit() { m_engineApplication.uninit(); };

        EngineApplication* get() override { return &m_engineApplication; }

    private:

        EngineApplication m_engineApplication;
    };
}

#include <engine/services/base/iservicecontainer.h>

#define gInternalEngineApplication puma::DefaultServices::getInstance()->get<puma::EngineApplicationService>()->get()