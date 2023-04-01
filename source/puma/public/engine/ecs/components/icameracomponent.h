#pragma once

#include <pina/component.h>

namespace puma
{
    class ICameraComponent : public pina::Component
    {
    public:

        virtual ~ICameraComponent(){}

        virtual float getMetersPerPixel() const = 0;
        virtual void setMetersPerPixel( float _metersPerPixel ) = 0;
    };
}