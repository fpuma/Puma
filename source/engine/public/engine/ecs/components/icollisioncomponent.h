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
        virtual PhysicsFrameID getFrameID() const = 0;

        virtual void addBody( PhysicsBodyInfo _bodyInfo ) = 0;
        virtual void addTrigger( PhysicsTriggerInfo _triggerInfo ) = 0;

        virtual bool isValid() const = 0;

    };
}