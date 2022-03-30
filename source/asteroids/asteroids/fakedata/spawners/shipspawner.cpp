#include <precompiledengine.h>
#include "shipspawner.h"

#include <asteroids/components/shipcomponent.h>
#include <asteroids/fakedata/input/inputconfig.h>
#include <asteroids/systems/shipmovementsystem.h>

#include <engine/ecs/base/providers/ientityprovider.h>
#include <engine/ecs/base/providers/icomponentprovider.h>
#include <engine/ecs/components/ilocationcomponent.h>
#include <engine/ecs/components/icollisioncomponent.h>
#include <engine/ecs/components/iinputcomponent.h>
#include <engine/services/iprovidersservice.h>
#include <engine/services/isystemsservice.h>
#include <engine/ecs/systems/icollisionsystem.h>
#include <engine/ecs/systems/iinputsystem.h>

Entity ShipSpawner::spawnShip( Position _pos )
{
    IEntityProvider* entityProvider = gProviders->get<IEntityProvider>();
    IComponentProvider* componentProvider = gProviders->get<IComponentProvider>();

    Entity shipEntity = entityProvider->requestEntity();

    //Location
    componentProvider->add<ILocationComponent>( shipEntity );

    //Input
    IInputComponent* inputComponent = componentProvider->add<IInputComponent>( shipEntity );
    for ( const auto& inputMap : kShipControllerJoystickInput )
    {
        inputComponent->addInputMap( inputMap.first, inputMap.second );
    }
    gSystems->get<IInputSystem>()->registerEntity( shipEntity );

    //Collision
    ICollisionComponent* collisionComponent = componentProvider->add<ICollisionComponent>( shipEntity );

    LeoFrameInfo frameInfo;
    frameInfo.linearDamping = 0.1f;
    gSystems->get<ICollisionSystem>()->registerEntity( shipEntity, frameInfo, LeoFrameType::Dynamic );

    LeoBodyInfo bodyInfo;
    Circle circle = { Vec2(), 25.0f };
    bodyInfo.shape.setAsCircle( circle );

    collisionComponent->addBody( bodyInfo );
    
    //Ship
    componentProvider->add<ShipComponent>( shipEntity );
    gSystems->get<ShipMovementSystem>()->setShipEntity(shipEntity);

    return shipEntity;
}

void ShipSpawner::unspawnShip( Entity _entity )
{
    IEntityProvider* entityProvider = gProviders->get<IEntityProvider>();
    IComponentProvider* componentProvider = gProviders->get<IComponentProvider>();

    gSystems->get<ICollisionSystem>()->unregisterEntity( _entity );

    componentProvider->remove<ILocationComponent>( _entity );
    componentProvider->remove<IInputComponent>( _entity );
    componentProvider->remove<ICollisionComponent>( _entity );

    gSystems->get<IInputSystem>()->unregisterEntity( _entity );

    entityProvider->disposeEntity( _entity );
}