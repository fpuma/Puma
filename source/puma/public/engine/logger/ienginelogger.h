#pragma once

namespace puma
{

    class IEngineLogger
    {
    public:

        virtual ~IEngineLogger() {}

        virtual void info( const char* _log ) = 0;
        virtual void warning( const char* _log ) = 0;
        virtual void error( const char* _log ) = 0;
    };

}