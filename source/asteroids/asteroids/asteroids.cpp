#include <precompiledengine.h>
#include "asteroids.h"


#include <asteroids/components/shipcomponent.h>
#include <asteroids/fakedata/spawners/shipspawner.h>
#include <asteroids/systems/shipmovementsystem.h>

#include <engine/ecs/components/icameracomponent.h>
#include <engine/ecs/components/ilocationcomponent.h>
#include <engine/services/iengineapplicationservice.h>
#include <engine/services/ecsservice.h>
#include <engine/ecs/systems/icollisionsystem.h>

using namespace puma;

void Asteroids::init()
{
    gEngineApplication->setWindowTitle( "Asteroids" );
    gEngineApplication->setWindowSize( 1000, 1000 );
    gEngineApplication->setWindowPosition( 200, 200 );

    //Register classes
    gSystems->registerSystem<ShipMovementSystem>();
    gSystems->addSystem<ShipMovementSystem>();
    gComponents->registerComponent<ShipComponent>();

    gSystems->subscribeSystemUpdate<ShipMovementSystem>( SystemUpdateId::PostPhysics );

    //Inits
    initCamera();
    initPhysics();
    
    //Spawn
    m_shipEntity = ShipSpawner::spawnShip( Position() );
}

void Asteroids::uninit()
{
    uninitCamera();
    ShipSpawner::unspawnShip( m_shipEntity );

    gSystems->unsubscribeSystemUpdate<ShipMovementSystem>( SystemUpdateId::PostPhysics );
    gSystems->removeSystem<ShipMovementSystem>();
}

void Asteroids::update( float _deltaTime )
{

}

void Asteroids::initPhysics()
{
    ICollisionSystem* collisionSystem = gSystems->getSystem<ICollisionSystem>();
    collisionSystem->init( { 0.0f, 0.0f } );
    collisionSystem->enableDebugDraw();
}

void Asteroids::initCamera()
{
    EntityProvider* entityProvider = gEntities;
    ComponentProvider* componentProvider = gComponents;

    m_cameraEntity = entityProvider->requestEntity();

    auto cameraComponent = componentProvider->addComponent<ICameraComponent>( m_cameraEntity );
    auto locationComponent = componentProvider->addComponent<ILocationComponent>( m_cameraEntity );

    cameraComponent->setMetersPerPixel( 1.0f );
    gEngineApplication->setCameraEntity( m_cameraEntity );
    locationComponent->setPosition( Position() );

}

void Asteroids::uninitCamera()
{
    EntityProvider* entityProvider = gEntities;
    ComponentProvider* componentProvider = gComponents;

    componentProvider->removeComponent<ICameraComponent>( m_cameraEntity );
    componentProvider->removeComponent<ILocationComponent>( m_cameraEntity );

    entityProvider->disposeEntity( m_cameraEntity );
}
