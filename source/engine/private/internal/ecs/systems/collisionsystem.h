#pragma once

#include <engine/ecs/systems/icollisionsystem.h>

namespace puma
{
    class CollisionSystem final : public ICollisionSystem
    {
    public:

        void init( physics::Vec2 _gravity ) override;
        void uninit() override;

        void registerEntity( Entity _entity, physics::FrameInfo _frameInfo, physics::FrameType _frameType ) override;
        void unregisterEntity( Entity _entity ) override;

        void update( float _deltaTime ) override {}
        void prePhysicsUpdate( float _deltaTime ) override {}
        void postPhysicsUpdate( float _deltaTime ) override;

        void setProperties( SystemProperties _properties ) override { m_properties = _properties; }
        SystemProperties getProperties() const override { return m_properties; }

        void setGravity( physics::Vec2 _gravity ) override;
        physics::Vec2 getGravity() override;

        void setCollisionCompatibility( const physics::CollisionCompatibility& _collisionCompatibility ) override;

    private:

#ifdef _DEBUG
        bool entityComponentCheck( Entity _entity );
#endif
        std::set<Entity> m_entities;
        SystemProperties m_properties;
        physics::WorldID m_worldId = physics::kInvalidPhysicsID;
    };
}