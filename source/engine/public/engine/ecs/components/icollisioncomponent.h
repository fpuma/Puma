#pragma once

#include <engine/ecs/base/icomponent.h>

#include <physics/simulation/frames/frameinfo.h>
#include <physics/simulation/frameparts/bodyinfo.h>
#include <physics/simulation/frameparts/triggerinfo.h>

namespace puma
{

    using namespace physics;

    class ICollisionComponent : public IComponent
    {
    public:

        virtual ~ICollisionComponent(){}

        virtual void init( FrameType _frameType, FrameInfo _frameInfo/*, WorldID _worldId*/ ) = 0;

        virtual FrameType getFrameType() const = 0;
        virtual FrameID getFrameID() const = 0;

        virtual void addBody( BodyInfo _bodyInfo ) = 0;
        virtual void addTrigger( TriggerInfo _triggerInfo ) = 0;

        virtual bool isValid() const = 0;

    };
}