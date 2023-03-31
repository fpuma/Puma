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
#include <engine/services/systemsservice.h>

#include <test/components/movedirectioncomponent.h>

namespace test
{
    puma::pina::Entity spawnBallSpawner( const InputActionKeyboardPairList& _keyboardInputList, const InputActionControllerPairList& _controllerInputList, const InputActionControllerButtonPairList& _controllerButtonInputList, const puma::Position& _position )
    {
        puma::pina::Entity result = gEntities->requestEntity();
        puma::pina::ComponentProvider* componentProvider = gComponents;

        auto locationComponent = componentProvider->add<puma::ILocationComponent>( result );
        auto inputComponent = componentProvider->add<puma::IInputComponent>( result );
        auto collisionComponent = componentProvider->add<puma::ICollisionComponent>( result );
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

        puma::leo::FrameInfo frameInfo;
        frameInfo.position = { locationComponent->getPosition().x, locationComponent->getPosition().y };
        frameInfo.gravityScale = 0.0f;
        frameInfo.preventRotation = true;
        
        collisionComponent->init( puma::leo::FrameType::Dynamic, frameInfo );

        puma::leo::BodyInfo bodyInfo;
        bodyInfo.collisionIndex = TestCollisionIndexes::BallSpawner;

        bodyInfo.shape.setAsCircle( { puma::Vec2(), 1.0f } );
        bodyInfo.restitution = 0.0f;

        collisionComponent->addBody( bodyInfo );

        return result;
    }

    void unspawnBallSpawner( puma::pina::Entity _spawnerEntity )
    {
        puma::pina::ComponentProvider* componentProvider = gComponents;

        componentProvider->remove<puma::ILocationComponent>( _spawnerEntity );
        componentProvider->remove<puma::IInputComponent>( _spawnerEntity );
        componentProvider->remove<puma::ICollisionComponent>( _spawnerEntity );
        componentProvider->remove<test::MoveDirectionComponent>( _spawnerEntity );

        gEntities->disposeEntity( _spawnerEntity );
    }
}