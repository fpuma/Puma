#include <precompiledengine.h>

#include <engine/ecs/base/entity.h>
#include <engine/services/iapplicationservice.h>
#include <engine/iengine.h>

#include <application/commondefinitions.h>
#include <texturemanager/itexturemanager.h>

#include <physics/simulation/world/iworld.h>
#include <physics/collisions/collissiondefinitions.h>

#include "test.h"

int main( int argc, char* argv[] )
{
    auto enginePtr = puma::IEngine::create();
    enginePtr->init();

    initPhysics();

    puma::app::Extent windowExtent = { 500,500,100,100 };
    puma::app::WindowHandle windowHandle = gApplication->createWindow( windowExtent, "EngineTest" );
    auto textureManagerPtr = puma::app::ITextureManager::create();

    puma::Entity floorEntity = spawnFloor( windowHandle, textureManagerPtr.get() );
    puma::Entity ballEntity = spawnBall( windowHandle, textureManagerPtr.get() );

    while ( !enginePtr->shouldQuit() )
    {
        enginePtr->update();
        enginePtr->render();
    };

    unspawnFloor( floorEntity );
    unspawnBall( ballEntity );

    enginePtr->uninit();

    return 0;
}

