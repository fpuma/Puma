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

        physics::FrameType getFrameType() const override { return m_frameType; }
        physics::FrameID getFrameID() const override { return m_frameId; }

        void addBody( physics::BodyInfo _bodyInfo ) override;
        void addTrigger( physics::TriggerInfo _triggerInfo ) override;

        bool isValid() const override { return (physics::FrameType::Invalid != m_frameType) && (m_frameId.value() != physics::kInvalidPhysicsID); }

    private:

        friend void CollisionSystem::registerEntity( Entity _entity, physics::FrameInfo _frameInfo, physics::FrameType _frameType );
        friend void CollisionSystem::unregisterEntity( Entity _entity );

        void init( physics::FrameType _frameType, physics::FrameID _frameId );
        void uninit();

        std::vector<physics::FramePartID> m_bodyIds;
        std::vector<physics::FramePartID> m_triggerIds;

        physics::FrameType m_frameType = physics::FrameType::Invalid;
        physics::FrameID m_frameId;
        bool m_enabled = true;
    };
}