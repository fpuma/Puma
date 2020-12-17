#pragma once

#include <engine/services/base/iservice.h>
#include <application/iapplication.h>

namespace puma
{
    class IApplicationService : public IService
    {
    public:
        
        virtual ~IApplicationService() {}

        virtual app::IApplication* get() = 0;
    };
}

#include <engine/services/base/iservicecontainer.h>

#define gApplication puma::DefaultServices::getInstance()->get<puma::IApplicationService>()->get()