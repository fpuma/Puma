#include <precompiledengine.h>
#include "asteroids.h"


#include <asteroids/components/shipcomponent.h>
#include <asteroids/fakedata/spawners/shipspawner.h>
#include <asteroids/systems/shipmovementsystem.h>

#include <engine/ecs/base/providers/ientityprovider.h>
#include <engine/ecs/base/providers/icomponentprovider.h>
#include <engine/ecs/components/icameracomponent.h>
#include <engine/ecs/components/ilocationcomponent.h>
#include <engine/services/iprovidersservice.h>
#include <engine/services/iengineapplicationservice.h>
#include <engine/services/isystemsservice.h>
#include <engine/ecs/systems/icollisionsystem.h>

using namespace puma;

void Asteroids::init()
{
    gEngineApplication->setWindowTitle( "Asteroids" );
    gEngineApplication->setWindowSize( 1000, 1000 );
    gEngineApplication->setWindowPosition( 200, 200 );

    //Register classes
    gSystems->registerClass<ShipMovementSystem>();
    gSystems->add<ShipMovementSystem>();
    gProviders->get<IComponentProvider>()->registerClass<ShipComponent>();

    //Inits
    initCamera();
    initPhysics();
    gSystems->updateSystemsProperties();
    
    //Spawn
    m_shipEntity = ShipSpawner::spawnShip( Position() );
}

void Asteroids::uninit()
{
    uninitCamera();
    ShipSpawner::unspawnShip( m_shipEntity );
}

void Asteroids::update( float _deltaTime )
{

}

void Asteroids::initPhysics()
{
    ICollisionSystem* collisionSystem = gSystems->get<ICollisionSystem>();
    collisionSystem->init( { 0.0f, 0.0f } );
    collisionSystem->enableDebugDraw();
}

void Asteroids::initCamera()
{
    IEntityProvider* entityProvider = gProviders->get<IEntityProvider>();
    IComponentProvider* componentProvider = gProviders->get<IComponentProvider>();

    m_cameraEntity = entityProvider->requestEntity();

    ICameraComponent* cameraComponent = componentProvider->add<ICameraComponent>( m_cameraEntity );
    ILocationComponent* locationComponent = componentProvider->add<ILocationComponent>( m_cameraEntity );

    cameraComponent->setMetersPerPixel( 1.0f );
    gEngineApplication->setCameraEntity( m_cameraEntity );
    locationComponent->setPosition( Position() );

}

void Asteroids::uninitCamera()
{
    IEntityProvider* entityProvider = gProviders->get<IEntityProvider>();
    IComponentProvider* componentProvider = gProviders->get<IComponentProvider>();

    componentProvider->remove<ICameraComponent>( m_cameraEntity );
    componentProvider->remove<ILocationComponent>( m_cameraEntity );

    entityProvider->disposeEntity( m_cameraEntity );
}
