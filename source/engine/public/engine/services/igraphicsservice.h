#pragma once

#include <engine/services/base/iservice.h>
#include <application/iapplication.h>

namespace puma
{
    class IGraphicsService : public IService
    {
    public:
        
        virtual ~IGraphicsService() {}

        virtual app::IApplication* get() = 0;
    };
}

#include <engine/services/base/iservicecontainer.h>

#define gGraphics puma::DefaultServices::getInstance()->get<puma::IGraphicsService>()->get()