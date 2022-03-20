#pragma once

#include <engine/application/iengineapplication.h>
#include <engine/services/base/iservice.h>

namespace puma
{
    class IEngineApplicationService : public IService
    {
    public:

        virtual ~IEngineApplicationService() {}

        virtual IEngineApplication* get() = 0;
    };
}

#include <engine/services/base/iservicecontainer.h>

#define gEngineApplication puma::DefaultServices::getInstance()->get<puma::IEngineApplicationService>()->get()