#pragma once

#include <modules/pina/component.h>

#include <modules/leo/leodefinitions.h>

namespace puma
{
    class ICollisionComponent : public Component
    {
    public:

        virtual ~ICollisionComponent(){}

        virtual leo::FrameType getFrameType() const = 0;

        virtual const leo::IDynamicFrame* getDynamicFrame() const = 0;
        virtual leo::IDynamicFrame* getDynamicFrame() = 0;

        virtual const leo::IKinematicFrame* getKinematicFrame() const = 0;
        virtual leo::IKinematicFrame* getKinematicFrame() = 0;

        virtual const leo::IStaticFrame* getStaticFrame() const = 0;
        virtual leo::IStaticFrame* getStaticFrame() = 0;

        virtual void addBody( const leo::BodyInfo& _bodyInfo ) = 0;
        virtual void addTrigger( const leo::TriggerInfo& _triggerInfo ) = 0;

        virtual bool isValid() const = 0;

    };
}