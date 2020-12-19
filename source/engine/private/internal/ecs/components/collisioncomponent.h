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

        FrameType getFrameType() const override { return m_frameType; }
        FrameID getFrameID() const override { return m_frameId; }

        void addBody( BodyInfo _bodyInfo ) override;
        void addTrigger( TriggerInfo _triggerInfo ) override;

        bool isValid() const override { return (FrameType::Invalid != m_frameType) && (m_frameId.value() != kInvalidPhysicsID); }

    private:

        friend void CollisionSystem::registerEntity( Entity _entity, FrameInfo _frameInfo );

        void init( FrameType _frameType, FrameID _frameId );

        std::vector<FramePartID> m_bodyIds;
        std::vector<FramePartID> m_triggerIds;

        FrameType m_frameType = FrameType::Invalid;
        FrameID m_frameId;
        bool m_enabled = true;
    };
}