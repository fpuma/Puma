#include <precompiledengine.h>

#include <engine/ecs/base/entity.h>
#include <engine/iengine.h>

#include <texturemanager/itexturemanager.h>

#include <physics/simulation/world/iworld.h>
#include <physics/collisions/collissiondefinitions.h>

#include "test.h"

int main( int argc, char* argv[] )
{
    auto enginePtr = puma::IEngine::create();
    enginePtr->init();

    initTest();

    auto textureManagerPtr = puma::app::ITextureManager::create();

    puma::Entity floorEntity = spawnFloor( textureManagerPtr.get() );
    puma::Entity ballEntity = spawnBall( textureManagerPtr.get() );

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

