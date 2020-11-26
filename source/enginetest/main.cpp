#include <precompiledengine.h>

#include <engine/iengine.h>
#include <engine/services/igraphicsservice.h>

#include <graphics/graphicdefinitions.h>

using namespace puma;

int main( int argc, char* argv[] )
{

    auto enginePtr = IEngine::create();
    enginePtr->init();

    gfx::Extent windowExtent = { 500,500,100,100 };
    gGraphics->init( windowExtent, "EngineTest" );

    while ( !enginePtr->shouldQuit() )
    {
        enginePtr->update();
        enginePtr->render();
    };

    enginePtr->uninit();

    return 0;
}