#pragma once
#include <pina/component.h>
#include <engine/utils/position.h>

namespace puma
{
    class ILocationComponent : public pina::Component
    {
    public:

        virtual ~ILocationComponent(){}

        virtual Position getPosition() const = 0;
        virtual void setPosition( const Position& _pos ) = 0;

        virtual void setRadiansRotation( float _angle ) = 0;
        virtual float getRadiansRotation() const = 0;
    };
}