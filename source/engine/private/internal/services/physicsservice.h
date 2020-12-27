#pragma once

//#include <engine/services/iphysicsservice.h>

#include <engine/services/base/iservice.h>
#include <physics/iphysics.h>

namespace puma
{
    class PhysicsService final : public IService
    {
    public:

        PhysicsService() { m_physics = physics::IPhysics::create(); }

        ~PhysicsService() { m_physics.reset(); }

        physics::IPhysics* get() { return m_physics.get(); }

        void uninit() {}

    private:

        std::unique_ptr<physics::IPhysics> m_physics;
    };

}

#include <engine/services/base/iservicecontainer.h>

#define gPhysics puma::DefaultServices::getInstance()->get<puma::PhysicsService>()->get()