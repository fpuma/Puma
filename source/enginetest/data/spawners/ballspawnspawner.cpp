#include <precompiledengine.h>

#include "ballspawnspawner.h"

#include <data/collisionindexes.h>

#include <engine/ecs/components/ilocationcomponent.h>
#include <engine/ecs/components/iinputcomponent.h>
#include <engine/ecs/components/icollisioncomponent.h>
#include <engine/ecs/systems/iinputsystem.h>
#include <engine/ecs/systems/icollisionsystem.h>
#include <modules/leo/leodefinitions.h>
#include <engine/services/ecsservice.h>

#include <test/components/movedirectioncomponent.h>

namespace test
{
    puma::Entity spawnBallSpawner( const InputActionKeyboardPairList& _keyboardInputList, const InputActionControllerPairList& _controllerInputList, const InputActionControllerButtonPairList& _controllerButtonInputList, const puma::Position& _position )
    {
        puma::Entity result = gEntities->requestEntity();
        puma::ComponentProvider* componentProvider = gComponents;

        auto locationComponent = componentProvider->addComponent<puma::ILocationComponent>( result );
        auto inputComponent = componentProvider->addComponent<puma::IInputComponent>( result );
        auto collisionComponent = componentProvider->addComponent<puma::ICollisionComponent>( result );
        componentProvider->addComponent<test::MoveDirectionComponent>( result );

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

        puma::leo::FrameInfo frameInfo;
        frameInfo.position = { locationComponent->getPosition().x, locationComponent->getPosition().y };
        frameInfo.gravityScale = 0.0f;
        frameInfo.preventRotation = true;
        gSystems->getSystem<puma::ICollisionSystem>()->registerEntity( result, frameInfo, puma::leo::FrameType::Dynamic );

        puma::leo::BodyInfo bodyInfo;
        bodyInfo.collisionIndex = TestCollisionIndexes::BallSpawner;

        bodyInfo.shape.setAsCircle( { puma::Vec2(), 1.0f } );
        bodyInfo.restitution = 0.0f;

        collisionComponent->addBody( bodyInfo );

        gSystems->getSystem<puma::IInputSystem>()->registerEntity( result );

        return result;
    }

    void unspawnBallSpawner( puma::Entity _spawnerEntity )
    {
        gSystems->getSystem<puma::IInputSystem>()->unregisterEntity( _spawnerEntity );
        gSystems->getSystem<puma::ICollisionSystem>()->unregisterEntity( _spawnerEntity );

        puma::ComponentProvider* componentProvider = gComponents;

        componentProvider->removeComponent<puma::ILocationComponent>( _spawnerEntity );
        componentProvider->removeComponent<puma::IInputComponent>( _spawnerEntity );
        componentProvider->removeComponent<puma::ICollisionComponent>( _spawnerEntity );
        componentProvider->removeComponent<test::MoveDirectionComponent>( _spawnerEntity );

        gEntities->disposeEntity( _spawnerEntity );
    }
}