#include <precompiledengine.h>

#include "ballspawnspawner.h"

#include <engine/ecs/base/providers/icomponentprovider.h>
#include <engine/ecs/base/providers/ientityprovider.h>
#include <engine/ecs/components/ilocationcomponent.h>
#include <engine/ecs/components/iinputcomponent.h>
#include <engine/ecs/components/icollisioncomponent.h>
#include <engine/ecs/systems/iinputsystem.h>
#include <engine/ecs/systems/icollisionsystem.h>
#include <engine/services/isystemsservice.h>
#include <engine/services/iprovidersservice.h>

#include <data/collisionindexes.h>

namespace test
{
    puma::Entity spawnBallSpawner( InputActionKeyboardPairList _keyboardInputList, const puma::Position& _position )
    {
        puma::Entity result = gProviders->get<puma::IEntityProvider>()->requestEntity();
        puma::IComponentProvider* componentProvider = gProviders->get<puma::IComponentProvider>();

        puma::ILocationComponent* locationComponent = componentProvider->add<puma::ILocationComponent>( result );
        puma::IInputComponent* inputComponent = componentProvider->add<puma::IInputComponent>( result );
        puma::ICollisionComponent* collisionComponent = componentProvider->add<puma::ICollisionComponent>( result );
        

        locationComponent->setPosition( _position );

        for ( InputActionKeyboardPairList::value_type keyboardInputPair : _keyboardInputList )
        {
            puma::KeyboardInput keyboardInput;
            keyboardInput.keyboardKey = keyboardInputPair.second.keyboardKey;
            keyboardInput.modifier = keyboardInputPair.second.modifier;
            keyboardInput.state = keyboardInputPair.second.state;

            inputComponent->addInputMap( keyboardInputPair.first, keyboardInput );
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

        gProviders->get<puma::IEntityProvider>()->disposeEntity( _spawnerEntity );
    }
}