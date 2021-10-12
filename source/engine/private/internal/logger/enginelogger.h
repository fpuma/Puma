#pragma once

#include <logger/logger.h>
#include <engine/logger/ienginelogger.h>

namespace puma
{
    class EngineLogger final : public IEngineLogger
    {
    public:

        EngineLogger();

        void info( const char* _log );
        void warning( const char* _log );
        void error( const char* _log );

        Logger* getLogger() { return &m_logger; }

    private:

        Logger m_logger;
        LogCategory m_logCategory;
    };
}