#pragma once

#include <modules/pina/system.h>
#include <modules/pina/entity.h>

using namespace puma;

namespace test
{
    class BallSpawnerSystem : public System
    {
    public:
        
        BallSpawnerSystem();

        void init();

        void uninit();
        void update( EntityProvider& _entityProvider, ComponentProvider& _componentProvider ) override;

        void queueRenderables( IRenderQueue& _renderQueue ) override;

    private:

        void updateSpawner( Entity _spawner );
        void renderDebugSpawner( Entity _spawner, IRenderQueue& _renderQueue );

        Entity m_spawner0;
        Entity m_spawner1;
        Entity m_spawnerHandler;

        float m_spawnerSpeed = 10.0f;

        std::vector<Entity> m_balls;
    };
}