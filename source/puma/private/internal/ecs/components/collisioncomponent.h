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

        leo::FrameID getFrameID() const { return m_frameId; }
        leo::FrameType getFrameType() const override { return m_frameType; }
        
        const leo::IDynamicFrame* getDynamicFrame() const override;
        leo::IDynamicFrame* getDynamicFrame() override;

        const leo::IKinematicFrame* getKinematicFrame() const override;
        leo::IKinematicFrame* getKinematicFrame() override;

        const leo::IStaticFrame* getStaticFrame() const override;
        leo::IStaticFrame* getStaticFrame() override;

        void addBody( const leo::BodyInfo& _bodyInfo ) override;
        void addTrigger( const leo::TriggerInfo& _triggerInfo ) override;

        bool isValid() const override { return (leo::FrameType::Invalid != m_frameType) && (m_frameId.value() != leo::kInvalidPhysicsID); }

    private:

        friend void CollisionSystem::registerEntity( Entity _entity, leo::FrameInfo _frameInfo, leo::FrameType _frameType );
        friend void CollisionSystem::unregisterEntity( Entity _entity );

        void init( leo::FrameType _frameType, leo::FrameID _frameId );
        void uninit();

        std::vector<leo::FramePartID> m_bodyIds;
        std::vector<leo::FramePartID> m_triggerIds;

        leo::FrameType m_frameType = leo::FrameType::Invalid;
        leo::FrameID m_frameId;
        bool m_enabled = true;
    };
}