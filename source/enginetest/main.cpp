#include <precompiledengine.h>

#include <engine/iengine.h>

#include "test/test.h"

int main( int argc, char* argv[] )
{
    //------------------------------------
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    _CrtSetBreakAlloc( -1 );
    //_CrtSetBreakAlloc( -1 );
    //---------------------------------------------------------------//

    auto enginePtr = puma::IEngine::create();
    enginePtr->init();

    test::Test gameTest;

    gameTest.initTest();

    while ( !enginePtr->shouldQuit() )
    {
        enginePtr->update();
        gameTest.updateTest();
        enginePtr->render();
    };

    gameTest.uninitTest();
    enginePtr->uninit();

    return 0;
}

