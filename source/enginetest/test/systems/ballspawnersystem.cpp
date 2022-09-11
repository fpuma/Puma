#include "precompiledengine.h"

#include "ballspawnersystem.h"

#include <data/inputactions.h>
#include <data/spawners/ballspawner.h>
#include <data/spawners/ballspawnspawner.h>

#include <engine/services/ecsservice.h>
#include <engine/ecs/components/icollisioncomponent.h>
#include <engine/ecs/components/iinputcomponent.h>
#include <engine/ecs/components/ilocationcomponent.h>
#include <engine/ecs/systems/iinputsystem.h>
#include <engine/ecs/systems/icollisionsystem.h>
#include <engine/renderer/irenderqueue.h>
#include <engine/services/iengineapplicationservice.h>
#include <engine/services/iloggerservice.h>

#include <test/components/movedirectioncomponent.h>

#include <utils/geometry/shapes/shape.h>

namespace test
{
    void BallSpawnerSystem::onInit()
    {
        m_spawner0 = spawnBallSpawner( kSpawner0KeyboardInput, kSpawner0ControllerJoystickInput, kSpawner0ControllerButtonInput, { -5.0f, 5.0f, 0.0f } );
        m_spawner1 = spawnBallSpawner( kSpawner1KeyboardInput, kSpawner1ControllerJoystickInput, kSpawner1ControllerButtonInput, { 5.0f, 5.0f, 0.0f } );

        m_spawnerHandler = gEntities->requestEntity();

        auto inputComponent = gComponents->addComponent<IInputComponent>( m_spawnerHandler );

        KeyboardInput keyboardInput;
        keyboardInput.keyboardKey = nina::KeyboardKey::KB_Y;
        inputComponent->addInputMap( TestInputActions::InvertGravity, keyboardInput );

        ControllerButtonInput controllerInput;
        controllerInput.controllerButton = nina::ControllerButton::CB_Y;
        controllerInput.controllerId = 0;
        inputComponent->addInputMap( TestInputActions::InvertGravity, controllerInput );

        gSystems->getSystem<IInputSystem>()->registerEntity( m_spawnerHandler );

        gSystems->subscribeSystemUpdate<BallSpawnerSystem>( SystemUpdateId::QueueRenderables );
        gSystems->subscribeSystemUpdate<BallSpawnerSystem>( SystemUpdateId::Update );
        gSystems->subscribeSystemUpdate<BallSpawnerSystem>( SystemUpdateId::CollisionStarted );
    }

    void BallSpawnerSystem::onUninit()
    {
        unspawnBallSpawner( m_spawner1 );
        unspawnBallSpawner( m_spawner0 );

        for ( puma::Entity entity : m_balls )
        {
            unspawnBall( entity );
        }

        gSystems->getSystem<IInputSystem>()->unregisterEntity( m_spawnerHandler );
        gComponents->removeComponent<IInputComponent>( m_spawnerHandler );
        gEntities->disposeEntity( m_spawnerHandler );

        gSystems->unsubscribeSystemUpdate<BallSpawnerSystem>( SystemUpdateId::QueueRenderables );
        gSystems->unsubscribeSystemUpdate<BallSpawnerSystem>( SystemUpdateId::Update );
        gSystems->unsubscribeSystemUpdate<BallSpawnerSystem>( SystemUpdateId::CollisionStarted );
    }

    void BallSpawnerSystem::update( EntityProvider& _entityProvider, ComponentProvider& _componentProvider )
    {
        updateSpawner( m_spawner0 );
        updateSpawner( m_spawner1 );

        IInputComponent* inputComponent = _componentProvider.getComponent<IInputComponent>(m_spawnerHandler);
        if ( inputComponent->isActionActive( TestInputActions::InvertGravity ) )
        {
            ICollisionSystem* collisionSystem = gSystems->getSystem<ICollisionSystem>();
            Vec2 currentGravity = collisionSystem->getGravity();
            collisionSystem->setGravity( currentGravity * -1.0f );
        }
    }
    
    void BallSpawnerSystem::queueRenderables( IRenderQueue& _renderQueue )
    {
        renderDebugSpawner( m_spawner0, _renderQueue );
        renderDebugSpawner( m_spawner1, _renderQueue );

        auto itCurrent = m_contactPointList.begin();

        while (itCurrent != m_contactPointList.end())
        {
            if (itCurrent->timer.isFinished())
            {
                itCurrent = m_contactPointList.erase( itCurrent );
            }
            else
            {
                Shape shape;
                shape.setAsCircle( { { 0.0f, 0.0f }, 0.5f } );
                RotationRadians rad = 0.0f;
                _renderQueue.addDebugRenderableShape( shape, Color::Red(), true, itCurrent->pos, rad );
                ++itCurrent;
            }
        }

    }

    void BallSpawnerSystem::onCollisionStarted( leo::FramePartID _framePartPtrA, leo::FramePartID _framePartPtrB, leo::ContactPoint _contactPoint )
    {
        ContactPointInfo contact;
        contact.timer.setTimeLimit( 0.5f );
        contact.timer.play();
        contact.pos = Position( _contactPoint.x, _contactPoint.y );

        m_contactPointList.push_back( contact );
    }

    void BallSpawnerSystem::updateSpawner( Entity _spawner )
    {
        puma::ComponentProvider* componentProvider = gComponents;

        puma::ILocationComponent* locationComponent = componentProvider->getComponent<puma::ILocationComponent>( _spawner );
        puma::IInputComponent* inputComponent = componentProvider->getComponent<puma::IInputComponent>( _spawner );


        if ( inputComponent->isActionActive( TestInputActions::SpawnBallAction ) )
        {
            m_balls.push_back( spawnBall( gEngineApplication->getTextureManager(), locationComponent->getPosition() ) );
            gLogger->info( puma::formatString( "Ball %d spawned!", m_balls.size() ).c_str() );
        }

        test::MoveDirectionComponent* moveDirectionComponent = componentProvider->getComponent<test::MoveDirectionComponent>( _spawner );
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
        puma::ICollisionComponent* collisionComponent = componentProvider->getComponent<puma::ICollisionComponent>( _spawner );
        leo::IDynamicFrame* dynamicFrame = collisionComponent->getDynamicFrame();
        dynamicFrame->setLinearVelocity( currentDir * m_spawnerSpeed );
    }

    void BallSpawnerSystem::renderDebugSpawner( Entity _spawner, IRenderQueue& _renderQueue )
    {
        puma::ComponentProvider* componentProvider = gComponents;

        puma::ILocationComponent* locationComponent = componentProvider->getComponent<puma::ILocationComponent>( _spawner );

        Shape circleShape;
        circleShape.setAsCircle( { Vec2(), 1.0f } );

        _renderQueue.addDebugRenderableShape( circleShape, Color::Red(), false, locationComponent->getPosition(), 0.0f );
    }
}
