#pragma once

#include <engine/ecs/base/containers/isystemcontainer.h>
#include <engine/services/base/iservice.h>

namespace puma
{
    class ISystemsService : public IService
    {
    public:

        virtual ~ISystemsService(){}

        virtual ISystemContainer* get() = 0;
    };
}

#include <engine/services/base/iservicecontainer.h>

#define gSystems puma::DefaultServices::getInstance()->get<puma::ISystemsService>()->get()