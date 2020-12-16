#include <precompiledengine.h>

#include <engine/iengine.h>
#include <engine/services/igraphicsservice.h>
#include <engine/ecs/base/entity.h>

#include <application/commondefinitions.h>
#include <application/irenderer.h>
#include <application/iwindow.h>
#include <texturemanager/itexturemanager.h>

using namespace puma;

Entity spawnFloor( app::WindowHandle _windowHandle, app::ITextureManager* _textureManager );
void unspawnFloor( Entity _floorEntity );

int main( int argc, char* argv[] )
{

    auto enginePtr = IEngine::create();
    enginePtr->init();

    app::Extent windowExtent = { 500,500,100,100 };
    

    app::WindowHandle windowHandle = gApplication->createWindow( windowExtent, "EngineTest" );

    auto textureManagerPtr = app::ITextureManager::create();

    //gApplication->getRenderer()->setDefaultBackgroundColor()

    Entity floorEntity = spawnFloor( windowHandle, textureManagerPtr.get() );

    while ( !enginePtr->shouldQuit() )
    {
        enginePtr->update();
        enginePtr->render();
    };

    unspawnFloor( floorEntity );

    enginePtr->uninit();

    return 0;
}


#include <engine/services/iprovidersservice.h>
#include <engine/services/isystemsservice.h>
#include <engine/ecs/base/providers/ientityprovider.h>
#include <engine/ecs/base/providers/icomponentprovider.h>

#include <texturemanager/itexturemanager.h>

#include <engine/ecs/components/irendercomponent.h>
#include <engine/ecs/components/ilocationcomponent.h>
#include <engine/ecs/components/icollisioncomponent.h>
#include <engine/ecs/systems/irendersystem.h>

Entity spawnFloor( app::WindowHandle _windowHandle, app::ITextureManager* _textureManager )
{
    Entity result = gProviders->get<IEntityProvider>()->requestEntity();
    IComponentProvider* componentProvider = gProviders->get<IComponentProvider>();

    ILocationComponent* locationComponent = componentProvider->add<ILocationComponent>( result );
    IRenderComponent* renderComponent = componentProvider->add<IRenderComponent>( result );
    //ICollisionComponent* collisionComponent = componentProvider->add<ICollisionComponent>( result );

    Position pos = { 0.0f, -5.0f };
    locationComponent->setPosition( pos );

    app::IRenderer* renderer = gApplication->getWindow( _windowHandle )->getRenderer();

    //Render
    app::Texture greenTexture = _textureManager->loadTexture( renderer, "../assets/green.png" );
    Renderable renderable;
    renderable.setTexture( greenTexture );
    renderComponent->setRenderable( renderable );
    RenderSize renderSize = { 200.0f, 50.0f };
    renderComponent->setSize( renderSize );
    
    gSystems->get<IRenderSystem>()->registerEntity( result );

    //Physics
    //FrameInfo frameInfo;
    //frameInfo.position = pos;
    //collisionComponent->init( physics::FrameType::Static, );

    //physics::Rectangle floorShape;
    //floorShape.lowerBoundary = { -100.0f, -25.0f };
    //floorShape.upperBoundary = { 100.0f, 25.0f };
    //physics::BodyInfo floorBodyInfo;
    //floorBodyInfo.collisionIndex = 0;
    //floorBodyInfo.shape.rectangle = floorShape;
    //floorBodyInfo.shapeType = ShapeType::Rectangle;
    //floorBodyInfo.restitution = 0.5f;


    return result;
}

void unspawnFloor( Entity _floorEntity )
{
    gSystems->get<IRenderSystem>()->unregisterEntity( _floorEntity );

    IComponentProvider* componentProvider = gProviders->get<IComponentProvider>();

    componentProvider->remove<ILocationComponent>( _floorEntity );
    componentProvider->remove<IRenderComponent>( _floorEntity );

    gProviders->get<IEntityProvider>()->disposeEntity( _floorEntity );

}