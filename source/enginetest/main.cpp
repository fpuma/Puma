#include <precompiledengine.h>

#include <engine/ecs/base/entity.h>
#include <engine/iengine.h>

#include "test.h"

int main( int argc, char* argv[] )
{
    auto enginePtr = puma::IEngine::create();
    enginePtr->init();

    initTest();

    while ( !enginePtr->shouldQuit() )
    {
        enginePtr->update();
        enginePtr->render();
    };

    uninitTest();

    enginePtr->uninit();

    return 0;
}

