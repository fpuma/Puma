#pragma once

#include <engine/services/base/iservice.h>
#include <time/itimereference.h>

namespace puma
{
    class ITimeService : public IService
    {
    public:
        
        virtual ~ITimeService() { }

        virtual ITimeReference* get() = 0;
    };
}

#include <engine/services/base/iservicecontainer.h>

#define gTime puma::DefaultServices::getInstance()->get<puma::ITimeService>()->get()