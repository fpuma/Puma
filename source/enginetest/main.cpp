#include <precompiledengine.h>

#include <engine/iengine.h>

#include "test/test.h"

int main( int argc, char* argv[] )
{
#ifdef _DEBUG
    //------------------------------------
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    
    //*
    _CrtSetBreakAlloc( -1 );
    /*/
    _CrtSetBreakAlloc( 4426 );
    //*/
    
    //---------------------------------------------------------------//
#endif

    auto gamePtr = std::make_unique<test::Test>();

    puma::IEngine::run( std::move(gamePtr) );

    return 0;
}

