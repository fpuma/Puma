#pragma once

#include <modules/pina/component.h>

namespace puma
{
    class ICameraComponent : public Component
    {
    public:

        virtual ~ICameraComponent(){}

        virtual float getMetersPerPixel() const = 0;
        virtual void setMetersPerPixel( float _metersPerPixel ) = 0;
    };
}