#pragma once

#include <engine/services/base/iservice.h>
#include <physics/iphysics.h>

namespace puma
{
    class IPhysicsService : public IService
    {
    public:

        virtual ~IPhysicsService() {};

        virtual physics::IPhysics* get() = 0;
    };
}

#include <engine/services/base/iservicecontainer.h>

#define gPhysics puma::DefaultServices::getInstance()->get<puma::IPhysicsService>()->get()