#pragma once

#include <modules/pina/entity.h>
#include <modules/pina/system.h>

#include <modules/leo/leodefinitions.h>

namespace puma
{
    class ICollisionSystem : public System
    {
    public:

        virtual ~ICollisionSystem() {}

        virtual void registerEntity( Entity _entity, leo::FrameInfo _frameInfo, leo::FrameType _frameType ) = 0;
        virtual void unregisterEntity( Entity _entity ) = 0;

        virtual void setGravity( Vec2 _gravity ) = 0;
        virtual Vec2 getGravity() = 0;

        virtual void setCollisionCompatibility( const leo::CollisionCompatibility& _collisionCompatibility ) = 0;

        virtual void enableDebugDraw() = 0;
        virtual void disableDebugDraw() = 0;
    };
}