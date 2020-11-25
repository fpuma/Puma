#pragma once

#include <engine/ecs/components/icollisioncomponent.h>
#include <engine/utils/position.h>

namespace puma
{

    using namespace physics;

    class CollisionComponent final : public ICollisionComponent
    {
    public:

        void enable() override { m_enabled = true; };
        void disable() override { m_enabled = false; };
        bool isEnabled() const override { return m_enabled; }

        void init( FrameType _frameType, FrameInfo _frameInfo/*, WorldID _worldId*/ ) override;

        FrameType getFrameType() const override { return m_frameType; }
        FrameID getFrameID() const override { return m_frameId; }

        void addBody( BodyInfo _bodyInfo ) override;
        void addTrigger( TriggerInfo _triggerInfo ) override;

        bool isValid() const override { return (FrameType::Count != m_frameType) && (m_frameId.value() != kInvalidPhysicsID); }

    private:

        std::vector<FramePartID> m_bodyIds;
        std::vector<FramePartID> m_triggerIds;

        FrameType m_frameType = FrameType::Count;
        FrameID m_frameId;
        bool m_enabled = true;
    };
}