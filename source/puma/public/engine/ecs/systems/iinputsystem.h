#pragma once

#include <pina/entity.h>
#include <engine/layers/isystem.h>

namespace puma
{
    class IInputSystem : public ISystem
    {
    public:

        virtual ~IInputSystem() {}

        virtual void registerEntity( pina::Entity _entity ) = 0;
        virtual void unregisterEntity( pina::Entity _entity ) = 0;
    };
}