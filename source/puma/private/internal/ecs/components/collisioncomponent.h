#pragma once

#include <engine/ecs/components/icollisioncomponent.h>
#include <engine/utils/position.h>

#include <internal/ecs/systems/collisionsystem.h>

namespace puma
{
    class CollisionComponent final : public ICollisionComponent
    {
    public:

        void onEnabled() override;
        void onDisabled() override;

        void init( leo::FrameType _frameType, leo::FrameInfo _frameInfo ) override;
        void uninit() override;

        leo::FrameID getFrameID() const { return m_frameId; }
        leo::FrameType getFrameType() const override { return m_frameType; }
        
        const leo::IDynamicFrame* getDynamicFrame() const override;
        leo::IDynamicFrame* getDynamicFrame() override;

        const leo::IKinematicFrame* getKinematicFrame() const override;
        leo::IKinematicFrame* getKinematicFrame() override;

        const leo::IStaticFrame* getStaticFrame() const override;
        leo::IStaticFrame* getStaticFrame() override;

        leo::FramePartID addBody( const leo::BodyInfo& _bodyInfo ) override;
        leo::FramePartID addTrigger( const leo::TriggerInfo& _triggerInfo ) override;

        bool isValid() const override { return (leo::FrameType::Invalid != m_frameType) && (m_frameId.value() != leo::kInvalidPhysicsID); }

    private:

        std::vector<leo::FramePartID> m_bodyIds;
        std::vector<leo::FramePartID> m_triggerIds;

        leo::FrameType m_frameType = leo::FrameType::Invalid;
        leo::FrameID m_frameId;
    };
}