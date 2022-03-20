#pragma once

#include <engine/ecs/base/icomponent.h>

namespace puma
{
    class ICameraComponent : public IComponent
    {
    public:

        virtual ~ICameraComponent(){}

        virtual float getMetersPerPixel() const = 0;
        virtual void setMetersPerPixel( float _metersPerPixel ) = 0;
    };
}