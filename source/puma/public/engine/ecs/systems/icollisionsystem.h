#pragma once

#include <pina/entity.h>
#include <engine/flow/system.h>

#include <modules/leo/leodefinitions.h>

namespace puma
{
    class ICollisionSystem : public System
    {
    public:

        virtual ~ICollisionSystem() {}

        virtual void registerEntity( pina::Entity _entity, leo::FrameInfo _frameInfo, leo::FrameType _frameType ) = 0;
        virtual void unregisterEntity( pina::Entity _entity ) = 0;

        virtual void setGravity( Vec2 _gravity ) = 0;
        virtual Vec2 getGravity() = 0;

        virtual void setCollisionCompatibility( const leo::CollisionCompatibility& _collisionCompatibility ) = 0;

        virtual void enableDebugDraw() = 0;
        virtual void disableDebugDraw() = 0;

        virtual const leo::UserCollisionData getUserCollisionData( leo::FramePartID _framePartId ) const = 0;
    };
}