#pragma once

#include <engine/services/iloggerservice.h>
#include <internal/logger/enginelogger.h>

namespace puma
{
    class LoggerService final : public ILoggerService
    {
    public:

        
        EngineLogger* get() override { return &m_engineLogger; }

    private:

        EngineLogger m_engineLogger;
    };
}

#include <engine/services/base/iservicecontainer.h>

#define gInternalLogger puma::DefaultServices::getInstance()->get<puma::LoggerService>()->get()