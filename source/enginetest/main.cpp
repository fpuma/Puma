#include <precompiledengine.h>

#include "debugphysics.h"

#include <engine/iengine.h>
#include <engine/services/iapplicationservice.h>
#include <engine/services/iphysicsservice.h>
#include <engine/ecs/base/entity.h>

#include <application/commondefinitions.h>
#include <application/irenderer.h>
#include <application/iwindow.h>
#include <texturemanager/itexturemanager.h>

#include <physics/simulation/world/iworld.h>
#include <physics/collisions/collissiondefinitions.h>

using namespace puma;

Entity spawnFloor( app::WindowHandle _windowHandle, app::ITextureManager* _textureManager );
void unspawnFloor( Entity _floorEntity );

Entity spawnBall( app::WindowHandle _windowHandle, app::ITextureManager* _textureManager );
void unspawnBall( Entity _floorEntity );

int main( int argc, char* argv[] )
{

    auto enginePtr = IEngine::create();
    enginePtr->init();

    app::Extent windowExtent = { 500,500,100,100 };
    

    app::WindowHandle windowHandle = gApplication->createWindow( windowExtent, "EngineTest" );
    

    auto textureManagerPtr = app::ITextureManager::create();

    gPhysics->getDefaultWorld()->setDebugDraw( std::move( std::make_unique<PhysicsTestDebugDraw>( gApplication->getDefaultRenderer() ) ) );

    gPhysics->getDefaultWorld()->setGravity( { 0.0f, -10.0f } );

    gPhysics->getDefaultWorld()->setCollisionCompatibility( { std::pair<physics::CollisionIndex, physics::CollisionIndex>( 0,0 ) } );

    Entity floorEntity = spawnFloor( windowHandle, textureManagerPtr.get() );
    Entity ballEntity = spawnBall( windowHandle, textureManagerPtr.get() );

    while ( !enginePtr->shouldQuit() )
    {
        enginePtr->update();
        enginePtr->render();
        //gPhysics->getDefaultWorld()->debugDraw();

    };

    unspawnFloor( floorEntity );
    unspawnBall( ballEntity );

    enginePtr->uninit();

    return 0;
}


#include <engine/services/iprovidersservice.h>
#include <engine/services/isystemsservice.h>
#include <engine/services/iphysicsservice.h>
#include <engine/ecs/base/providers/ientityprovider.h>
#include <engine/ecs/base/providers/icomponentprovider.h>

#include <texturemanager/itexturemanager.h>

#include <engine/ecs/components/irendercomponent.h>
#include <engine/ecs/components/ilocationcomponent.h>
#include <engine/ecs/components/icollisioncomponent.h>
#include <engine/ecs/systems/irendersystem.h>
#include <engine/ecs/systems/icollisionsystem.h>

#include <physics/simulation/frames/istaticframe.h>
#include <physics/simulation/frames/idynamicframe.h>

Entity spawnFloor( app::WindowHandle _windowHandle, app::ITextureManager* _textureManager )
{
    Entity result = gProviders->get<IEntityProvider>()->requestEntity();
    IComponentProvider* componentProvider = gProviders->get<IComponentProvider>();

    ILocationComponent* locationComponent = componentProvider->add<ILocationComponent>( result );
    IRenderComponent* renderComponent = componentProvider->add<IRenderComponent>( result );
    ICollisionComponent* collisionComponent = componentProvider->add<ICollisionComponent>( result );
    
    gSystems->get<IRenderSystem>()->registerEntity( result );
    gSystems->get<ICollisionSystem>()->registerEntity( result );

    Position pos = { 0.0f, -50.0f };
    locationComponent->setPosition( pos );

    app::IRenderer* renderer = gApplication->getWindow( _windowHandle )->getRenderer();

    //Render
    app::Texture greenTexture = _textureManager->loadTexture( renderer, "../assets/green.png" );
    Renderable renderable;
    renderable.setTexture( greenTexture );
    renderComponent->setRenderable( renderable );
    RenderSize renderSize = { 200.0f, 50.0f };
    renderComponent->setSize( renderSize );
    

    //Physics
    FrameInfo frameInfo;
    frameInfo.position = pos;
    collisionComponent->init( physics::FrameType::Static, frameInfo);

    physics::Rectangle floorShape;
    floorShape.lowerBoundary = { -100.0f, -25.0f };
    floorShape.upperBoundary = { 100.0f, 25.0f };
    physics::BodyInfo floorBodyInfo;
    floorBodyInfo.collisionIndex = 0;
    floorBodyInfo.shape.rectangle = floorShape;
    floorBodyInfo.shapeType = ShapeType::Rectangle;
    floorBodyInfo.restitution = 0.5f;

    IStaticFrame* staticFrame = gPhysics->getStaticFrame( collisionComponent->getFrameID() );
    staticFrame->addBody( floorBodyInfo );

    return result;
}

void unspawnFloor( Entity _floorEntity )
{
    gSystems->get<IRenderSystem>()->unregisterEntity( _floorEntity );
    gSystems->get<ICollisionSystem>()->unregisterEntity( _floorEntity );

    IComponentProvider* componentProvider = gProviders->get<IComponentProvider>();

    componentProvider->remove<ILocationComponent>( _floorEntity );
    componentProvider->remove<IRenderComponent>( _floorEntity );

    gProviders->get<IEntityProvider>()->disposeEntity( _floorEntity );

}

Entity spawnBall( app::WindowHandle _windowHandle, app::ITextureManager* _textureManager )
{
    Entity result = gProviders->get<IEntityProvider>()->requestEntity();
    IComponentProvider* componentProvider = gProviders->get<IComponentProvider>();

    ILocationComponent* locationComponent = componentProvider->add<ILocationComponent>( result );
    IRenderComponent* renderComponent = componentProvider->add<IRenderComponent>( result );
    ICollisionComponent* collisionComponent = componentProvider->add<ICollisionComponent>( result );

    gSystems->get<IRenderSystem>()->registerEntity( result );
    gSystems->get<ICollisionSystem>()->registerEntity( result );

    Position pos = { 0.0f, 50.0f };
    locationComponent->setPosition( pos );

    app::IRenderer* renderer = gApplication->getWindow( _windowHandle )->getRenderer();

    //Render
    app::Texture tennisTexture = _textureManager->loadTexture( renderer, "../assets/tennisball.png" );
    Renderable renderable;
    renderable.setTexture( tennisTexture );
    renderComponent->setRenderable( renderable );
    RenderSize renderSize = { 30.0f, 30.0f };
    renderComponent->setSize( renderSize );


    //Physics
    FrameInfo frameInfo;
    frameInfo.position = pos;
    collisionComponent->init( physics::FrameType::Dynamic, frameInfo );

    physics::Circle ballShape;
    ballShape.radius = 15.0f;
    physics::BodyInfo ballBodyInfo;
    ballBodyInfo.density = 1.0f;
    ballBodyInfo.collisionIndex = 0;
    ballBodyInfo.shape.circle = ballShape;
    ballBodyInfo.shapeType = ShapeType::Circle;
    ballBodyInfo.restitution = 0.5f;

    IDynamicFrame* dynamicFrame = gPhysics->getDynamicFrame( collisionComponent->getFrameID() );
    dynamicFrame->addBody( ballBodyInfo );

    return result;
}

void unspawnBall( Entity _ballEntity )
{
    gSystems->get<IRenderSystem>()->unregisterEntity( _ballEntity );
    gSystems->get<ICollisionSystem>()->unregisterEntity( _ballEntity );

    IComponentProvider* componentProvider = gProviders->get<IComponentProvider>();

    componentProvider->remove<ILocationComponent>( _ballEntity );
    componentProvider->remove<IRenderComponent>( _ballEntity );

    gProviders->get<IEntityProvider>()->disposeEntity( _ballEntity );
}