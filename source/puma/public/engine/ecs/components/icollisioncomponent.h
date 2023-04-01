#pragma once

#include <pina/component.h>

#include <modules/leo/leodefinitions.h>

namespace puma
{
    class ICollisionComponent : public pina::Component
    {
    public:

        virtual ~ICollisionComponent(){}

        virtual void init( leo::FrameType _frameType, leo::FrameInfo _frameInfo ) = 0;
        virtual void uninit() = 0;

        virtual leo::FrameType getFrameType() const = 0;

        virtual const leo::IDynamicFrame* getDynamicFrame() const = 0;
        virtual leo::IDynamicFrame* getDynamicFrame() = 0;

        virtual const leo::IKinematicFrame* getKinematicFrame() const = 0;
        virtual leo::IKinematicFrame* getKinematicFrame() = 0;

        virtual const leo::IStaticFrame* getStaticFrame() const = 0;
        virtual leo::IStaticFrame* getStaticFrame() = 0;

        virtual leo::FramePartID addBody( const leo::BodyInfo& _bodyInfo ) = 0;
        virtual leo::FramePartID addTrigger( const leo::TriggerInfo& _triggerInfo ) = 0;

        virtual bool isValid() const = 0;

    };
}