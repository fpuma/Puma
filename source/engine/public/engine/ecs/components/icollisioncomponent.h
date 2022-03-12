#pragma once

#include <engine/ecs/base/icomponent.h>

#include <engine/physics/physicsdefinitions.h>

namespace puma
{
    class ICollisionComponent : public IComponent
    {
    public:

        virtual ~ICollisionComponent(){}

        virtual PhysicsFrameType getFrameType() const = 0;

        virtual const PhysicsDynamicFrame* getDynamicFrame() const = 0;
        virtual PhysicsDynamicFrame* getDynamicFrame() = 0;

        virtual const PhysicsKinematicFrame* getKinematicFrame() const = 0;
        virtual PhysicsKinematicFrame* getKinematicFrame() = 0;

        virtual const PhysicsStaticFrame* getStaticFrame() const = 0;
        virtual PhysicsStaticFrame* getStaticFrame() = 0;

        virtual void addBody( const PhysicsBodyInfo& _bodyInfo ) = 0;
        virtual void addTrigger( const PhysicsTriggerInfo& _triggerInfo ) = 0;

        virtual bool isValid() const = 0;

    };
}