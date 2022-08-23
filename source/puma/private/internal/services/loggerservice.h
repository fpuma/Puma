#pragma once

#include <engine/services/iloggerservice.h>
#include <internal/logger/enginelogger.h>

namespace puma
{
    class LoggerService final : public ILoggerService
    {
    public:

        LoggerService() { m_engineLogger = std::make_unique<EngineLogger>(); }

        ~LoggerService() { m_engineLogger.reset(); }

        EngineLogger* get() override { return m_engineLogger.get(); }

    private:

        std::unique_ptr<EngineLogger> m_engineLogger;
    };
}

#include <engine/services/base/iservicecontainer.h>

#define gInternalLogger puma::DefaultServices::getInstance()->get<puma::LoggerService>()->get()