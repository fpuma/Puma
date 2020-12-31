#include <precompiledapplication.h>
#include <precompiledphysics.h>
#include <precompiledengine.h>

#include "test.h"
#include "debugphysics.h"

#include <application/iwindow.h>
#include <texturemanager/itexturemanager.h>

#include <engine/services/iprovidersservice.h>
#include <engine/services/isystemsservice.h>

#include <engine/ecs/base/providers/icomponentprovider.h>
#include <engine/ecs/base/providers/ientityprovider.h>

#include <engine/ecs/components/icameracomponent.h>
#include <engine/ecs/components/icollisioncomponent.h>
#include <engine/ecs/components/ilocationcomponent.h>
#include <engine/ecs/components/irendercomponent.h>

#include <engine/ecs/systems/icollisionsystem.h>
#include <engine/ecs/systems/irendersystem.h>

#include <physics/collisions/collissiondefinitions.h>

#include <physics/simulation/world/iworld.h>
#include <physics/simulation/frames/istaticframe.h>
#include <physics/simulation/frames/idynamicframe.h>

#include <utils/graphics/dimensions.h>

void setCamera()
{
     puma::Entity cameraEntity = gSystems->get<puma::IRenderSystem>()->getCameraEntity();
     puma::ICameraComponent* cameraComponent = gProviders->get<puma::IComponentProvider>()->get<puma::ICameraComponent>( cameraEntity );

     cameraComponent->setMetersPerPixel( 0.1f );
}

void initTest()
{
    initWindow();
    initPhysics();
    setCamera();

    gSystems->updateSystemsProperties();
}

void initWindow()
{
    puma::Extent windowExtent = { 500,500,100,100 };
    auto renderSystemPtr = gSystems->get<puma::IRenderSystem>();
    renderSystemPtr->init( windowExtent, "EngineTest" );
}

void initPhysics()
{
    auto collisitonSystemPtr = gSystems->get<puma::ICollisionSystem>();
    collisitonSystemPtr->init( { 0.0f, -10.0f } );
    collisitonSystemPtr->setCollisionCompatibility( { std::pair<puma::physics::CollisionIndex, puma::physics::CollisionIndex>( 0,0 ) } );
}

puma::Entity spawnFloor( puma::app::ITextureManager* _textureManager )
{
    puma::Entity result = gProviders->get<puma::IEntityProvider>()->requestEntity();
    puma::IComponentProvider* componentProvider = gProviders->get<puma::IComponentProvider>();

    puma::ILocationComponent* locationComponent = componentProvider->add<puma::ILocationComponent>( result );
    puma::IRenderComponent* renderComponent = componentProvider->add<puma::IRenderComponent>( result );
    puma::ICollisionComponent* collisionComponent = componentProvider->add<puma::ICollisionComponent>( result );

    puma::IRenderSystem* renderSystem = gSystems->get<puma::IRenderSystem>();

    puma::Position pos = { 0.0f, -20.0f };
    locationComponent->setPosition( pos );

    puma::app::IRenderer* renderer = renderSystem->getRenderer();

    //Render
    puma::app::Texture greenTexture = _textureManager->loadTexture( renderer, "../assets/green.png" );
    puma::Renderable renderable;
    renderable.setTexture( greenTexture );
    renderComponent->setRenderable( renderable );
    puma::RenderSize renderSize = { 40.0f, 8.0f };
    renderComponent->setSize( renderSize );

    gSystems->get<puma::IRenderSystem>()->registerEntity( result );

    //Physics
    puma::physics::FrameInfo frameInfo;
    frameInfo.position = pos;
    frameInfo.angle = 10.0f;

    gSystems->get<puma::ICollisionSystem>()->registerEntity( result, frameInfo, puma::physics::FrameType::Static );

    puma::physics::Rectangle floorShape;
    floorShape.lowerBoundary = { -20.0f, -4.0f };
    floorShape.upperBoundary = { 20.0f, 4.0f };
    puma::physics::BodyInfo floorBodyInfo;
    floorBodyInfo.collisionIndex = 0;
    floorBodyInfo.shape.rectangle = floorShape;
    floorBodyInfo.shapeType = puma::physics::ShapeType::Rectangle;
    floorBodyInfo.restitution = 0.0f;

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

    puma::Position pos = { 0.0f, 0.0f };
    locationComponent->setPosition( pos );

    puma::app::IRenderer* renderer = renderSystem->getRenderer();

    //Render
    puma::app::Texture tennisTexture = _textureManager->loadTexture( renderer, "../assets/tennisball.png" );
    puma::Renderable renderable;
    renderable.setTexture( tennisTexture );
    renderComponent->setRenderable( renderable );
    puma::RenderSize renderSize = { 5.0f, 5.0f };
    renderComponent->setSize( renderSize );
    renderSystem->registerEntity( result );


    //Physics
    puma::physics::FrameInfo frameInfo;
    frameInfo.position = pos;
    gSystems->get<puma::ICollisionSystem>()->registerEntity( result, frameInfo, puma::physics::FrameType::Dynamic );

    puma::physics::Circle ballShape;
    ballShape.radius = 2.5f;
    puma::physics::BodyInfo ballBodyInfo;
    ballBodyInfo.density = 1.0f;
    ballBodyInfo.collisionIndex = 0;
    ballBodyInfo.shape.circle = ballShape;
    ballBodyInfo.shapeType = puma::physics::ShapeType::Circle;
    ballBodyInfo.restitution = 0.5f;

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