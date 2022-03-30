#include "precompiledengine.h"

#include "ballspawnersystem.h"

#include <data/inputactions.h>
#include <data/spawners/ballspawner.h>
#include <data/spawners/ballspawnspawner.h>

#include <engine/ecs/base/providers/ientityprovider.h>
#include <engine/ecs/base/providers/icomponentprovider.h>
#include <engine/ecs/components/icollisioncomponent.h>
#include <engine/ecs/components/iinputcomponent.h>
#include <engine/ecs/components/ilocationcomponent.h>
#include <engine/ecs/systems/iinputsystem.h>
#include <engine/ecs/systems/icollisionsystem.h>
#include <engine/renderer/irenderqueue.h>
#include <engine/services/iengineapplicationservice.h>
#include <engine/services/iloggerservice.h>
#include <engine/services/iprovidersservice.h>
#include <engine/services/isystemsservice.h>

#include <test/components/movedirectioncomponent.h>

#include <utils/geometry/shapes/shape.h>

namespace test
{
    BallSpawnerSystem::BallSpawnerSystem()
    {
        m_systemProperties.updateBitMask = SystemUpdateFlag_Update | SystemUpdateFlag_QueueRenderables;
    }

    void BallSpawnerSystem::init()
    {
        m_spawner0 = spawnBallSpawner( kSpawner0KeyboardInput, kSpawner0ControllerJoystickInput, kSpawner0ControllerButtonInput, { -5.0f, 5.0f, 0.0f } );
        m_spawner1 = spawnBallSpawner( kSpawner1KeyboardInput, kSpawner1ControllerJoystickInput, kSpawner1ControllerButtonInput, { 5.0f, 5.0f, 0.0f } );

        m_spawnerHandler = gProviders->get<IEntityProvider>()->requestEntity();

        IInputComponent* inputComponent = gProviders->get<IComponentProvider>()->add<IInputComponent>( m_spawnerHandler );

        KeyboardInput keyboardInput;
        keyboardInput.keyboardKey = NinaKeyboardKey::KB_Y;
        inputComponent->addInputMap( TestInputActions::InvertGravity, keyboardInput );
        gSystems->get<IInputSystem>()->registerEntity( m_spawnerHandler );
    }

    void BallSpawnerSystem::uninit()
    {
        unspawnBallSpawner( m_spawner1 );
        unspawnBallSpawner( m_spawner0 );

        for ( puma::Entity entity : m_balls )
        {
            unspawnBall( entity );
        }

        gSystems->get<IInputSystem>()->unregisterEntity( m_spawnerHandler );
        gProviders->get<IComponentProvider>()->remove<IInputComponent>( m_spawnerHandler );
        gProviders->get<IEntityProvider>()->disposeEntity( m_spawnerHandler );
    }

    void BallSpawnerSystem::update( float _deltaTime )
    {
        updateSpawner( m_spawner0 );
        updateSpawner( m_spawner1 );

        IInputComponent* inputComponent = gProviders->get<IComponentProvider>()->get<IInputComponent>(m_spawnerHandler);
        if ( inputComponent->isActionActive( TestInputActions::InvertGravity ) )
        {
            ICollisionSystem* collisionSystem = gSystems->get<ICollisionSystem>();
            Vec2 currentGravity = collisionSystem->getGravity();
            collisionSystem->setGravity( currentGravity * -1.0f );
        }
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
        LeoDynamicFrame* dynamicFrame = collisionComponent->getDynamicFrame();
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
