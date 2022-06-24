#pragma once

#include <engine/ecs/base/icomponent.h>

#include <engine/external/leodefinitions.h>

namespace puma
{
    class ICollisionComponent : public IComponent
    {
    public:

        virtual ~ICollisionComponent(){}

        virtual LeoFrameType getFrameType() const = 0;

        virtual const LeoDynamicFrame* getDynamicFrame() const = 0;
        virtual LeoDynamicFrame* getDynamicFrame() = 0;

        virtual const LeoKinematicFrame* getKinematicFrame() const = 0;
        virtual LeoKinematicFrame* getKinematicFrame() = 0;

        virtual const LeoStaticFrame* getStaticFrame() const = 0;
        virtual LeoStaticFrame* getStaticFrame() = 0;

        virtual void addBody( const LeoBodyInfo& _bodyInfo ) = 0;
        virtual void addTrigger( const LeoTriggerInfo& _triggerInfo ) = 0;

        virtual bool isValid() const = 0;

    };
}