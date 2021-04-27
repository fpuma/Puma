#pragma once

#include <engine/ecs/components/icollisioncomponent.h>
#include <engine/utils/position.h>

#include <internal/ecs/systems/collisionsystem.h>

namespace puma
{
    class CollisionComponent final : public ICollisionComponent
    {
    public:

        void enable() override { m_enabled = true; };
        void disable() override { m_enabled = false; };
        bool isEnabled() const override { return m_enabled; }

        PhysicsFrameType getFrameType() const override { return m_frameType; }
        PhysicsFrameID getFrameID() const override { return m_frameId; }

        void addBody( const PhysicsBodyInfo& _bodyInfo ) override;
        void addTrigger( const PhysicsTriggerInfo& _triggerInfo ) override;

        bool isValid() const override { return (physics::FrameType::Invalid != m_frameType) && (m_frameId.value() != physics::kInvalidPhysicsID); }

    private:

        friend void CollisionSystem::registerEntity( Entity _entity, physics::FrameInfo _frameInfo, physics::FrameType _frameType );
        friend void CollisionSystem::unregisterEntity( Entity _entity );

        void init( PhysicsFrameType _frameType, PhysicsFrameID _frameId );
        void uninit();

        std::vector<physics::FramePartID> m_bodyIds;
        std::vector<physics::FramePartID> m_triggerIds;

        PhysicsFrameType m_frameType = PhysicsFrameType::Invalid;
        PhysicsFrameID m_frameId;
        bool m_enabled = true;
    };
}