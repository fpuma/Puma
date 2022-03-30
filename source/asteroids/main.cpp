#include <precompiledengine.h>

#include <engine/iengine.h>

#include <asteroids/asteroids.h>

int main( int argc, char* argv[] )
{
#ifdef _DEBUG
    //------------------------------------
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    _CrtSetBreakAlloc( -1 );
    //_CrtSetBreakAlloc( 2356 );
    //---------------------------------------------------------------//
#endif

    auto enginePtr = puma::IEngine::create();
    enginePtr->init( { 1000, 1000, 200, 200 }, "Asteroids" );

    Asteroids asteroidsGame;

    asteroidsGame.init();

    while ( !enginePtr->shouldQuit() )
    {
        enginePtr->update();
        enginePtr->render();
    };

    asteroidsGame.uninit();
    enginePtr->uninit();

    return 0;
}