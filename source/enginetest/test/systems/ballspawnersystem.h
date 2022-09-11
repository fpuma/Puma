#pragma once

#include <modules/pina/system.h>
#include <modules/pina/entity.h>
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

    class BallSpawnerSystem : public System
    {
    public:
        
        void onInit() override;
        void onUninit() override;

        void update( EntityProvider& _entityProvider, ComponentProvider& _componentProvider ) override;

        void queueRenderables( IRenderQueue& _renderQueue ) override;

        void onCollisionStarted( leo::FramePartID _framePartPtrA, leo::FramePartID _framePartPtrB, leo::ContactPoint _contactPoint ) override;

    private:

        void updateSpawner( Entity _spawner );
        void renderDebugSpawner( Entity _spawner, IRenderQueue& _renderQueue );

        Entity m_spawner0;
        Entity m_spawner1;
        Entity m_spawnerHandler;

        float m_spawnerSpeed = 10.0f;

        std::vector<Entity> m_balls;

        std::vector<ContactPointInfo> m_contactPointList;
    };
}