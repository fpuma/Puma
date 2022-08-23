#pragma once

#include <modules/pina/entity.h>
#include <modules/pina/system.h>

namespace puma
{
    class IInputSystem : public System
    {
    public:

        virtual ~IInputSystem() {}

        virtual void registerEntity( Entity _entity ) = 0;
        virtual void unregisterEntity( Entity _entity ) = 0;
    };
}