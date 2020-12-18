#pragma once

#include <engine/ecs/systems/icollisionsystem.h>

namespace puma
{
    class CollisionSystem final : public ICollisionSystem
    {
    public:

        void init() override;
        void uninit() override;

        void registerEntity( Entity _entity ) override;
        void unregisterEntity( Entity _entity ) override;

        void update( float _deltaTime ) override {}
        void prePhysicsUpdate( float _deltaTime ) override {}
        void postPhysicsUpdate( float _deltaTime ) override;

        void setProperties( SystemProperties _properties ) override { m_properties = _properties; }
        SystemProperties getProperties() const override { return m_properties; }

    private:

#ifdef _DEBUG
        bool entityComponentCheck( Entity _entity );
#endif
        std::set<Entity> m_entities;
        SystemProperties m_properties;
    };
}