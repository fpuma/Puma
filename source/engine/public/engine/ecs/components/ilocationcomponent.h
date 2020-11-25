#pragma once
#include <engine/ecs/base/icomponent.h>
#include <engine/utils/position.h>

namespace puma
{
    class ILocationComponent : public IComponent
    {
    public:

        virtual ~ILocationComponent(){}

        virtual Position getPosition() const = 0;
        virtual void setPosition( const Position& _pos ) = 0;

        virtual void setDegreesRotation( float _angle ) = 0;
        virtual float getDegreesRotation() const = 0;
    };
}