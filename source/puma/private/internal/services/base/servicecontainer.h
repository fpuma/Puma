#pragma once

#include <engine/services/base/iservicecontainer.h>

namespace puma
{
    class ServiceContainer final : public IServiceContainer
    {
    public:
        ServiceContainer();
        ~ServiceContainer();
        
        ServiceContainer( const ServiceContainer& _services ) = delete;
        ServiceContainer& operator =( const ServiceContainer& _services ) = delete;

        void init();
        void uninit();
    };
}