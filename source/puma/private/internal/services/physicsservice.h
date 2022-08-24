#pragma once

//#include <engine/services/iphysicsservice.h>

#include <engine/services/base/iservice.h>
#include <leo/iphysics.h>

namespace puma
{
    class PhysicsService final : public IService
    {
    public:

        PhysicsService() { m_physics = leo::IPhysics::create(); }

        ~PhysicsService() { m_physics.reset(); }

        leo::IPhysics* get() { return m_physics.get(); }

    private:

        std::unique_ptr<leo::IPhysics> m_physics;
    };

}

#include <engine/services/base/iservicecontainer.h>

#define gPhysics puma::DefaultServices::getInstance()->get<puma::PhysicsService>()->get()