#include "precompiledengine.h"

#include "ballspawnersystem.h"

#include <data/inputactions.h>
#include <data/spawners/ballspawner.h>
#include <data/spawners/ballspawnspawner.h>
#include <engine/ecs/base/providers/icomponentprovider.h>
#include <engine/ecs/components/icollisioncomponent.h>
#include <engine/ecs/components/iinputcomponent.h>
#include <engine/ecs/components/ilocationcomponent.h>
#include <engine/renderer/irenderqueue.h>
#include <engine/services/iengineapplicationservice.h>
#include <engine/services/iloggerservice.h>
#include <engine/services/iprovidersservice.h>
#include <utils/geometry/shapes/shape.h>

namespace test
{
    BallSpawnerSystem::BallSpawnerSystem()
    {
        m_systemProperties.updateBitMask = static_cast<SystemUpdateBitMask>(SystemUpdateFlag::Update) | static_cast<SystemUpdateBitMask>(SystemUpdateFlag::QueueRenderables);
    }

    void BallSpawnerSystem::init()
    {
        m_spawner0 = spawnBallSpawner( kSpawner0KeyboardInput, { -5.0f, 5.0f, 0.0f } );
        m_spawner1 = spawnBallSpawner( kSpawner1KeyboardInput, { 5.0f, 5.0f, 0.0f } );
    }

    void BallSpawnerSystem::uninit()
    {
        unspawnBallSpawner( m_spawner1 );
        unspawnBallSpawner( m_spawner0 );

        for ( puma::Entity entity : m_balls )
        {
            unspawnBall( entity );
        }
    }

    void BallSpawnerSystem::update( float _deltaTime )
    {
        updateSpawner( m_spawner0 );
        updateSpawner( m_spawner1 );
    }
    
    void BallSpawnerSystem::queueRenderables( IRenderQueue& _renderQueue )
    {
        renderDebugSpawner( m_spawner0, _renderQueue );
        renderDebugSpawner( m_spawner1, _renderQueue );
    }

    void BallSpawnerSystem::updateSpawner( Entity _spawner )
    {
        puma::IComponentProvider* componentProvider = gProviders->get<puma::IComponentProvider>();

        puma::ILocationComponent* locationComponent = componentProvider->get<puma::ILocationComponent>( _spawner );
        puma::IInputComponent* inputComponent = componentProvider->get<puma::IInputComponent>( _spawner );


        if ( inputComponent->isActionActive( TestInputActions::SpawnBallAction ) )
        {
            m_balls.push_back( spawnBall( gEngineApplication->getTextureManager(), locationComponent->getPosition() ) );
            gLogger->info( puma::formatString( "Ball %d spawned!", m_balls.size() ).c_str() );
        }
    }

    void BallSpawnerSystem::renderDebugSpawner( Entity _spawner, IRenderQueue& _renderQueue )
    {
        puma::IComponentProvider* componentProvider = gProviders->get<puma::IComponentProvider>();

        puma::ILocationComponent* locationComponent = componentProvider->get<puma::ILocationComponent>( _spawner );

        Shape circleShape;
        circleShape.setAsCircle( { Vec2(), 1.0f } );

        _renderQueue.addRenderableShape( circleShape, Color::Red(), false, locationComponent->getPosition(), 0.0f, true);
    }
}
