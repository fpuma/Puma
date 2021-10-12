#include <precompiledengine.h>
#include "enginelogger.h"

namespace puma
{
    EngineLogger::EngineLogger()
    {
        m_logCategory = m_logger.registerCategory( "PumaEngine" );
    }

    void EngineLogger::info( const char* _log )
    {
        m_logger.info( m_logCategory, _log );
    }

    void EngineLogger::warning( const char* _log )
    {
        m_logger.warning( m_logCategory, _log );
    }
    
    void EngineLogger::error( const char* _log )
    {
        m_logger.error( m_logCategory, _log );
    }
}