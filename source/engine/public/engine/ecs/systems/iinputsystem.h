#pragma once

#include <engine/ecs/base/entity.h>
#include <engine/ecs/base/isystem.h>

namespace puma
{
    class IInputSystem : public ISystem
    {
    public:

        virtual ~IInputSystem() {}

        virtual void registerEntity( Entity _entity ) = 0;
        virtual void unregisterEntity( Entity _entity ) = 0;
    };
}