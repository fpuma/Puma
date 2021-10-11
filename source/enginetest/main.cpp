#include <precompiledengine.h>

#include <engine/iengine.h>

#include "test.h"

int main( int argc, char* argv[] )
{
    //------------------------------------
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    _CrtSetBreakAlloc( -1 );
    //_CrtSetBreakAlloc( -1 );
    //---------------------------------------------------------------//

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

