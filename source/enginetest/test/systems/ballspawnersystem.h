#pragma once

#include <engine/ecs/base/isystem.h>
#include <engine/ecs/base/entity.h>

using namespace puma;

namespace test
{
    class BallSpawnerSystem : public ISystem
    {
    public:
        
        BallSpawnerSystem();

        void init();

        void uninit() override;
        void update( float _deltaTime ) override;
        void prePhysicsUpdate( float _deltaTime ) override {};
        void postPhysicsUpdate( float _deltaTime ) override {};

        void queueRenderables( IRenderQueue& _renderQueue ) override;

        void setProperties( SystemProperties _properties ) override { m_systemProperties = _properties; }
        SystemProperties getProperties() const override { return m_systemProperties; }

    private:

        void updateSpawner( Entity _spawner );
        void renderDebugSpawner( Entity _spawner, IRenderQueue& _renderQueue );

        Entity m_spawner0;
        Entity m_spawner1;
        Entity m_spawnerHandler;
        SystemProperties m_systemProperties;

        float m_spawnerSpeed = 10.0f;

        std::vector<Entity> m_balls;
    };
}