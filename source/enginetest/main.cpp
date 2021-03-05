#include <precompiledengine.h>

#include <engine/ecs/base/entity.h>
#include <engine/iengine.h>

#include <texturemanager/itexturemanager.h>
#include <engine/services/iengineapplicationservice.h>

#include "test.h"

int main( int argc, char* argv[] )
{
    auto enginePtr = puma::IEngine::create();
    enginePtr->init();

    initTest();

    auto textureManagerPtr = gEngineApplication->getTextureManager();

    puma::Entity floorEntity = spawnFloor( textureManagerPtr );
    puma::Entity ballEntity = spawnBall( textureManagerPtr );

    while ( !enginePtr->shouldQuit() )
    {
        enginePtr->update();
        enginePtr->render();
    };

    unspawnFloor( floorEntity );
    unspawnBall( ballEntity );

    uninitTest();

    enginePtr->uninit();

    return 0;
}

