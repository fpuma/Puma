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
    auto asteroidsPtr = std::make_unique<Asteroids>();
    
    enginePtr->run( std::move(asteroidsPtr) );

    return 0;
}