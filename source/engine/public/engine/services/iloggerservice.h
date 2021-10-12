#pragma once

#include <engine/logger/ienginelogger.h>
#include <engine/services/base/iservice.h>

namespace puma
{
    class ILoggerService : public IService
    {
    public:

        virtual ~ILoggerService() {}

        virtual IEngineLogger* get() = 0;
    };
}

#include <engine/services/base/iservicecontainer.h>

#define gLogger puma::DefaultServices::getInstance()->get<puma::ILoggerService>()->get()