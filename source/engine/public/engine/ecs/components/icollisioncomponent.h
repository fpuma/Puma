#pragma once

#include <engine/ecs/base/icomponent.h>

#include <physics/simulation/frames/frameinfo.h>
#include <physics/simulation/frameparts/bodyinfo.h>
#include <physics/simulation/frameparts/triggerinfo.h>

namespace puma
{
    class ICollisionComponent : public IComponent
    {
    public:

        virtual ~ICollisionComponent(){}

        virtual physics::FrameType getFrameType() const = 0;
        virtual physics::FrameID getFrameID() const = 0;

        virtual void addBody( physics::BodyInfo _bodyInfo ) = 0;
        virtual void addTrigger( physics::TriggerInfo _triggerInfo ) = 0;

        virtual bool isValid() const = 0;

    };
}