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

#include <test/components/movedirectioncomponent.h>

#include <utils/geometry/shapes/shape.h>

namespace test
{
    BallSpawnerSystem::BallSpawnerSystem()
    {
        m_systemProperties.updateBitMask = static_cast<SystemUpdateBitMask>(SystemUpdateFlag::Update) | static_cast<SystemUpdateBitMask>(SystemUpdateFlag::QueueRenderables);
    }

    void BallSpawnerSystem::init()
    {
        m_spawner0 = spawnBallSpawner( kSpawner0KeyboardInput, kSpawner0ControllerJoystickInput, kSpawner0ControllerButtonInput, { -5.0f, 5.0f, 0.0f } );
        m_spawner1 = spawnBallSpawner( kSpawner1KeyboardInput, kSpawner1ControllerJoystickInput, kSpawner1ControllerButtonInput, { 5.0f, 5.0f, 0.0f } );
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

        test::MoveDirectionComponent* moveDirectionComponent = componentProvider->get<test::MoveDirectionComponent>( _spawner );
        Vec2 currentDir = moveDirectionComponent->getDirection();
        Vec2 inputDir;
        if ( inputComponent->isActionActive( TestInputActions::MoveBallSpawnerStartUp ) ) inputDir = inputDir + Vec2( { 0.0f, 1.0f } );
        if ( inputComponent->isActionActive( TestInputActions::MoveBallSpawnerStartDown ) ) inputDir = inputDir + Vec2( { 0.0f, -1.0f } );
        if ( inputComponent->isActionActive( TestInputActions::MoveBallSpawnerStartLeft ) ) inputDir = inputDir + Vec2( { -1.0f, 0.0f } );
        if ( inputComponent->isActionActive( TestInputActions::MoveBallSpawnerStartRight ) ) inputDir = inputDir + Vec2( { 1.0f, 0.0f } );

        if ( inputComponent->isActionActive( TestInputActions::MoveBallSpawnerStopUp ) ) inputDir = inputDir + Vec2( { 0.0f, -1.0f } );
        if ( inputComponent->isActionActive( TestInputActions::MoveBallSpawnerStopDown ) ) inputDir = inputDir + Vec2( { 0.0f, 1.0f } );
        if ( inputComponent->isActionActive( TestInputActions::MoveBallSpawnerStopLeft ) ) inputDir = inputDir + Vec2( { 1.0f, 0.0f } );
        if ( inputComponent->isActionActive( TestInputActions::MoveBallSpawnerStopRight ) ) inputDir = inputDir + Vec2( { -1.0f, 0.0f } );

        bool controllerInput = false;
        if ( inputComponent->isActionActive( TestInputActions::MoveBallSpawner ) )
        {
            InputActionExtraInfo joystickDir = inputComponent->getInputActionExtraInfo( TestInputActions::MoveBallSpawner );
            inputDir = { joystickDir.x, joystickDir.y };
            controllerInput = true;
        }

        inputDir = inputDir.normalize();

        currentDir = controllerInput ? inputDir : currentDir + inputDir;

        moveDirectionComponent->setDirection( currentDir );
        puma::ICollisionComponent* collisionComponent = componentProvider->get<puma::ICollisionComponent>( _spawner );
        PhysicsDynamicFrame* dynamicFrame = collisionComponent->getDynamicFrame();
        dynamicFrame->setLinearVelocity( currentDir * m_spawnerSpeed );
    }

    void BallSpawnerSystem::renderDebugSpawner( Entity _spawner, IRenderQueue& _renderQueue )
    {
        puma::IComponentProvider* componentProvider = gProviders->get<puma::IComponentProvider>();

        puma::ILocationComponent* locationComponent = componentProvider->get<puma::ILocationComponent>( _spawner );

        Shape circleShape;
        circleShape.setAsCircle( { Vec2(), 1.0f } );

        _renderQueue.addRenderableShape( circleShape, Color::Red(), false, locationComponent->getPosition(), 0.0f, {}, true );
    }
}
