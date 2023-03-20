#pragma once

#include <pina/entity.h>
#include <engine/flow/system.h>

namespace puma
{
    class IInputSystem : public System
    {
    public:

        virtual ~IInputSystem() {}

        virtual void registerEntity( pina::Entity _entity ) = 0;
        virtual void unregisterEntity( pina::Entity _entity ) = 0;
    };
}