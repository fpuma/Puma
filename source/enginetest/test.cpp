#include <precompiledapplication.h>
#include <precompiledphysics.h>
#include <precompiledengine.h>

#include "test.h"
#include "debugphysics.h"

#include <application/iwindow.h>
#include <texturemanager/itexturemanager.h>

#include <engine/services/iprovidersservice.h>
#include <engine/services/isystemsservice.h>
#include <engine/services/iengineapplicationservice.h>

#include <engine/ecs/base/providers/icomponentprovider.h>
#include <engine/ecs/base/providers/ientityprovider.h>

#include <engine/ecs/components/icameracomponent.h>
#include <engine/ecs/components/icollisioncomponent.h>
#include <engine/ecs/components/ilocationcomponent.h>
#include <engine/ecs/components/irendercomponent.h>

#include <engine/ecs/systems/icollisionsystem.h>
#include <engine/ecs/systems/irendersystem.h>

#include <engine/physics/physicsdefinitions.h>

#include <utils/graphics/dimensions.h>


namespace
{

    puma::Entity MyDefaultCamera = puma::kInvalidEntity;

    puma::Entity buildDefaultCamera()
    {
        puma::IEntityProvider* entityProvider = gProviders->get<puma::IEntityProvider>();
        puma::IComponentProvider* componentProvider = gProviders->get<puma::IComponentProvider>();

        puma::Entity result = entityProvider->requestEntity();
        puma::ILocationComponent* locationComponent = componentProvider->add<puma::ILocationComponent>( result );
        puma::ICameraComponent* cameraComponent = componentProvider->add<puma::ICameraComponent>( result );

        locationComponent->setPosition( { 0.0f, 0.0f } );
        cameraComponent->setMetersPerPixel( 0.1f );

        return result;
    }

    void destroyDefaultCamera( puma::Entity _entity )
    {
        puma::IEntityProvider* entityProvider = gProviders->get<puma::IEntityProvider>();
        puma::IComponentProvider* componentProvider = gProviders->get<puma::IComponentProvider>();

        componentProvider->remove<puma::ICameraComponent>( _entity );
        componentProvider->remove<puma::ILocationComponent>( _entity );

        entityProvider->disposeEntity( _entity );
    }

}


void setCamera()
{
    MyDefaultCamera = buildDefaultCamera();
    gEngineApplication->setCameraEntity( MyDefaultCamera );
}

void initTest()
{
    initWindow();
    initPhysics();
    setCamera();

    gSystems->updateSystemsProperties();
}

void uninitTest()
{
    destroyDefaultCamera( MyDefaultCamera );
}

void initWindow()
{
    puma::Extent windowExtent = { 500,500,100,100 };
    gEngineApplication->init( windowExtent, "EngineTest" );
}

void initPhysics()
{
    auto collisitonSystemPtr = gSystems->get<puma::ICollisionSystem>();
    collisitonSystemPtr->init( { 0.0f, -10.0f } );
    collisitonSystemPtr->setCollisionCompatibility( { std::pair<puma::PhysicsCollisionIndex, puma::PhysicsCollisionIndex>( 0,0 ) } );
}

puma::Entity spawnFloor( puma::app::ITextureManager* _textureManager )
{
    puma::Entity result = gProviders->get<puma::IEntityProvider>()->requestEntity();
    puma::IComponentProvider* componentProvider = gProviders->get<puma::IComponentProvider>();

    puma::ILocationComponent* locationComponent = componentProvider->add<puma::ILocationComponent>( result );
    puma::IRenderComponent* renderComponent = componentProvider->add<puma::IRenderComponent>( result );
    puma::ICollisionComponent* collisionComponent = componentProvider->add<puma::ICollisionComponent>( result );

    puma::Position pos = { 0.0f, -20.0f, 0.0f };
    locationComponent->setPosition( pos );

    //Render
    puma::app::Texture greenTexture = _textureManager->loadTexture( "../assets/green.png" );
    puma::TextureInfo textureInfo;
    textureInfo.texture = greenTexture;
    textureInfo.renderSize = { 40.0f, 8.0f };
    
    renderComponent->addTextureInfo( textureInfo );

    gSystems->get<puma::IRenderSystem>()->registerEntity( result );

    //Physics
    puma::PhysicsFrameInfo frameInfo;
    frameInfo.position = { pos.x, pos.y };
    frameInfo.angle = 45.0f;

    gSystems->get<puma::ICollisionSystem>()->registerEntity( result, frameInfo, puma::PhysicsFrameType::Static );

    puma::Rectangle floorShape;
    floorShape.lowerBoundary = { -20.0f, -4.0f };
    floorShape.upperBoundary = { 20.0f, 4.0f };
    puma::PhysicsBodyInfo floorBodyInfo;
    floorBodyInfo.collisionIndex = 0;
    floorBodyInfo.shape.rectangle = floorShape;
    floorBodyInfo.shapeType = puma::ShapeType::Rectangle;
    floorBodyInfo.restitution = 0.7f;

    collisionComponent->addBody( floorBodyInfo );

    return result;
}

void unspawnFloor( puma::Entity _floorEntity )
{
    gSystems->get<puma::IRenderSystem>()->unregisterEntity( _floorEntity );
    gSystems->get<puma::ICollisionSystem>()->unregisterEntity( _floorEntity );

    puma::IComponentProvider* componentProvider = gProviders->get<puma::IComponentProvider>();

    componentProvider->remove<puma::ILocationComponent>( _floorEntity );
    componentProvider->remove<puma::IRenderComponent>( _floorEntity );
    componentProvider->remove<puma::ICollisionComponent>( _floorEntity );

    gProviders->get<puma::IEntityProvider>()->disposeEntity( _floorEntity );

}

puma::Entity spawnBall( puma::app::ITextureManager* _textureManager )
{
    puma::Entity result = gProviders->get<puma::IEntityProvider>()->requestEntity();
    puma::IComponentProvider* componentProvider = gProviders->get<puma::IComponentProvider>();

    puma::ILocationComponent* locationComponent = componentProvider->add<puma::ILocationComponent>( result );
    puma::IRenderComponent* renderComponent = componentProvider->add<puma::IRenderComponent>( result );
    puma::ICollisionComponent* collisionComponent = componentProvider->add<puma::ICollisionComponent>( result );

    puma::IRenderSystem* renderSystem = gSystems->get<puma::IRenderSystem>();

    puma::Position pos = { 0.0f, 20.0f, 0.0f };
    locationComponent->setPosition( pos );

    //Render
    puma::app::Texture tennisTexture = _textureManager->loadTexture( "../assets/tennisball.png" );
    puma::TextureInfo textureInfo;
    textureInfo.texture = tennisTexture;
    textureInfo.renderSize = { 5.0f, 5.0f };
    textureInfo.textureSample = { 1.5f,1.5f };

    renderComponent->addTextureInfo( textureInfo );
    renderSystem->registerEntity( result );


    //Physics
    puma::PhysicsFrameInfo frameInfo;
    frameInfo.position = { pos.x, pos.y };
    gSystems->get<puma::ICollisionSystem>()->registerEntity( result, frameInfo, puma::PhysicsFrameType::Dynamic );

    puma::Circle ballShape;
    ballShape.radius = 2.5f;
    puma::PhysicsBodyInfo ballBodyInfo;
    ballBodyInfo.density = 1.0f;
    ballBodyInfo.collisionIndex = 0;
    ballBodyInfo.shape.circle = ballShape;
    ballBodyInfo.shapeType = puma::ShapeType::Circle;
    ballBodyInfo.restitution = 0.6f;

    collisionComponent->addBody( ballBodyInfo );

    return result;
}

void unspawnBall( puma::Entity _ballEntity )
{
    gSystems->get<puma::IRenderSystem>()->unregisterEntity( _ballEntity );
    gSystems->get<puma::ICollisionSystem>()->unregisterEntity( _ballEntity );

    puma::IComponentProvider* componentProvider = gProviders->get<puma::IComponentProvider>();

    componentProvider->remove<puma::ILocationComponent>( _ballEntity );
    componentProvider->remove<puma::IRenderComponent>( _ballEntity );
    componentProvider->remove<puma::ICollisionComponent>( _ballEntity );

    gProviders->get<puma::IEntityProvider>()->disposeEntity( _ballEntity );
}