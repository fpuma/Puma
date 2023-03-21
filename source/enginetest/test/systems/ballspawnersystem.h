#pragma once

#include <engine/layers/isystem.h>
#include <pina/entity.h>
#include <time/timers/countdowntimer.h>
#include <engine/utils/position.h>

using namespace puma;

namespace test
{
    struct ContactPointInfo
    {
        ContactPointInfo operator = ( const ContactPointInfo& _other ) 
        {
            return {};
        }

        Position pos;
        CountdownTimer timer;
    };

    class BallSpawnerSystem : public ISystem
    {
    public:
        
        void onInit() override;
        void onUninit() override;

        void update( pina::EntityProvider& _entityProvider, pina::ComponentProvider& _componentProvider ) override;

        void queueRenderables( IRenderQueue& _renderQueue ) override;

        void onCollisionStarted( leo::FramePartID _framePartPtrA, leo::FramePartID _framePartPtrB, leo::ContactPoint _contactPoint ) override;

    private:

        void updateSpawner( pina::Entity _spawner );
        void renderDebugSpawner( pina::Entity _spawner, IRenderQueue& _renderQueue );

        pina::Entity m_spawner0;
        pina::Entity m_spawner1;
        pina::Entity m_spawnerHandler;

        float m_spawnerSpeed = 10.0f;

        std::vector<pina::Entity> m_balls;

        std::vector<ContactPointInfo> m_contactPointList;
    };
}