#pragma once

#include <engine/ecs/base/entity.h>
#include <engine/ecs/base/isystem.h>

#include <physics/simulation/frames/frameinfo.h>

namespace puma
{
    class ICollisionSystem : public ISystem
    {
    public:

        virtual ~ICollisionSystem() {}

        virtual void init( Vec2 _gravity ) = 0;

        virtual void registerEntity( Entity _entity, physics::FrameInfo _frameInfo, physics::FrameType _frameType ) = 0;
        virtual void unregisterEntity( Entity _entity ) = 0;

        virtual void setGravity( Vec2 _gravity ) = 0;
        virtual Vec2 getGravity() = 0;

        virtual void setCollisionCompatibility( const physics::CollisionCompatibility& _collisionCompatibility ) = 0;
    };
}