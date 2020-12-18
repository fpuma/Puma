#pragma once

#include <engine/ecs/base/entity.h>
#include <engine/ecs/base/isystem.h>

namespace puma
{

    class ICollisionSystem : public ISystem
    {
    public:

        virtual ~ICollisionSystem() {}

        virtual void init() = 0;

        virtual void registerEntity( Entity _entity ) = 0;
        virtual void unregisterEntity( Entity _entity ) = 0;
    };
}