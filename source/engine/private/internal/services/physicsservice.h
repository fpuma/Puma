#pragma once

#include <engine/services/iphysicsservice.h>

namespace puma
{
    class PhysicsService final : public IPhysicsService
    {
    public:

        PhysicsService() { m_physics = physics::IPhysics::create(); }

        ~PhysicsService() { m_physics.reset(); }

        physics::IPhysics* get() override { return m_physics.get(); }

        void uninit() {}

    private:

        std::unique_ptr<physics::IPhysics> m_physics;
    };

}