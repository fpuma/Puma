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

        LeoFrameID getFrameID() const { return m_frameId; }
        LeoFrameType getFrameType() const override { return m_frameType; }
        
        const LeoDynamicFrame* getDynamicFrame() const override;
        LeoDynamicFrame* getDynamicFrame() override;

        const LeoKinematicFrame* getKinematicFrame() const override;
        LeoKinematicFrame* getKinematicFrame() override;

        const LeoStaticFrame* getStaticFrame() const override;
        LeoStaticFrame* getStaticFrame() override;

        void addBody( const LeoBodyInfo& _bodyInfo ) override;
        void addTrigger( const LeoTriggerInfo& _triggerInfo ) override;

        bool isValid() const override { return (LeoFrameType::Invalid != m_frameType) && (m_frameId.value() != leo::kInvalidPhysicsID); }

    private:

        friend void CollisionSystem::registerEntity( Entity _entity, LeoFrameInfo _frameInfo, LeoFrameType _frameType );
        friend void CollisionSystem::unregisterEntity( Entity _entity );

        void init( LeoFrameType _frameType, LeoFrameID _frameId );
        void uninit();

        std::vector<LeoFramePartID> m_bodyIds;
        std::vector<LeoFramePartID> m_triggerIds;

        LeoFrameType m_frameType = LeoFrameType::Invalid;
        LeoFrameID m_frameId;
        bool m_enabled = true;
    };
}