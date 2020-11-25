#pragma once

#include <engine/services/base/iprovidercontainer.h>
#include <engine/services/base/iservice.h>

namespace puma
{
    class IProvidersService : public IService
    {
    public:

        virtual ~IProvidersService() { }

        virtual IProviderContainer* get() = 0;
    };
}

#include <engine/services/base/iservicecontainer.h>

#define gProviders puma::DefaultServices::getInstance()->get<puma::IProvidersService>()->get()