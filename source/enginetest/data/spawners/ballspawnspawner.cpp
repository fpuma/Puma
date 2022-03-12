#include <precompiledengine.h>

#include "ballspawnspawner.h"

#include <data/collisionindexes.h>

#include <engine/ecs/base/providers/icomponentprovider.h>
#include <engine/ecs/base/providers/ientityprovider.h>
#include <engine/ecs/components/ilocationcomponent.h>
#include <engine/ecs/components/iinputcomponent.h>
#include <engine/ecs/components/icollisioncomponent.h>
#include <engine/ecs/systems/iinputsystem.h>
#include <engine/ecs/systems/icollisionsystem.h>
#include <engine/services/isystemsservice.h>
#include <engine/services/iprovidersservice.h>

#include <test/components/movedirectioncomponent.h>

namespace test
{
    puma::Entity spawnBallSpawner( const InputActionKeyboardPairList& _keyboardInputList, const InputActionControllerPairList& _controllerInputList, const InputActionControllerButtonPairList& _controllerButtonInputList, const puma::Position& _position )
    {
        puma::Entity result = gProviders->get<puma::IEntityProvider>()->requestEntity();
        puma::IComponentProvider* componentProvider = gProviders->get<puma::IComponentProvider>();

        puma::ILocationComponent* locationComponent = componentProvider->add<puma::ILocationComponent>( result );
        puma::IInputComponent* inputComponent = componentProvider->add<puma::IInputComponent>( result );
        puma::ICollisionComponent* collisionComponent = componentProvider->add<puma::ICollisionComponent>( result );
        componentProvider->add<test::MoveDirectionComponent>( result );

        locationComponent->setPosition( _position );

        for ( InputActionKeyboardPairList::value_type keyboardInputPair : _keyboardInputList )
        {
            inputComponent->addInputMap( keyboardInputPair.first, keyboardInputPair.second );
        }
        
        for ( InputActionControllerPairList::value_type controllerInputPair : _controllerInputList )
        {
            inputComponent->addInputMap( controllerInputPair.first, controllerInputPair.second );
        }

        for ( InputActionControllerButtonPairList::value_type controllerInputPair : _controllerButtonInputList )
        {
            inputComponent->addInputMap( controllerInputPair.first, controllerInputPair.second );
        }

        puma::PhysicsFrameInfo frameInfo;
        frameInfo.position = { locationComponent->getPosition().x, locationComponent->getPosition().y };
        frameInfo.gravityScale = 0.0f;
        frameInfo.preventRotation = true;
        gSystems->get<puma::ICollisionSystem>()->registerEntity( result, frameInfo, puma::PhysicsFrameType::Dynamic );

        puma::PhysicsBodyInfo bodyInfo;
        bodyInfo.collisionIndex = TestCollisionIndexes::BallSpawner;

        bodyInfo.shape.setAsCircle( { puma::Vec2(), 1.0f } );
        bodyInfo.restitution = 0.0f;

        collisionComponent->addBody( bodyInfo );

        gSystems->get<puma::IInputSystem>()->registerEntity( result );

        return result;
    }

    void unspawnBallSpawner( puma::Entity _spawnerEntity )
    {
        gSystems->get<puma::IInputSystem>()->unregisterEntity( _spawnerEntity );
        gSystems->get<puma::ICollisionSystem>()->unregisterEntity( _spawnerEntity );

        puma::IComponentProvider* componentProvider = gProviders->get<puma::IComponentProvider>();

        componentProvider->remove<puma::ILocationComponent>( _spawnerEntity );
        componentProvider->remove<puma::IInputComponent>( _spawnerEntity );
        componentProvider->remove<puma::ICollisionComponent>( _spawnerEntity );
        componentProvider->remove<test::MoveDirectionComponent>( _spawnerEntity );

        gProviders->get<puma::IEntityProvider>()->disposeEntity( _spawnerEntity );
    }
}