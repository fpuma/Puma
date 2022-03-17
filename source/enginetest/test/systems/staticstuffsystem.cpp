#include "precompiledengine.h"
#include "staticstuffsystem.h"

#include <data/spawners/backgroundspawner.h>
#include <engine/services/iengineapplicationservice.h>
#include <engine/renderer/irenderqueue.h>

namespace test
{
    StaticStuffSystem::StaticStuffSystem()
    {
        m_systemProperties.updateBitMask = static_cast<SystemUpdateBitMask>(SystemUpdateFlag::QueueRenderables);
    }

    void StaticStuffSystem::init()
    {
        m_backgroundEntity = spawnBackground( gEngineApplication->getTextureManager(), { 0.0f, 0.0f, 0.0f } );
    }

    void StaticStuffSystem::uninit()
    {
        unspawnBackground( m_backgroundEntity );
    }

    void StaticStuffSystem::queueRenderables( IRenderQueue& _renderQueue )
    {
        int yOffset = 400;
        _renderQueue.addScreenRenderableText( "Spawner A:", Color::White(), { 20, yOffset } );
        _renderQueue.addScreenRenderableText( "    Move: W,S,A,D or L_STICK", Color::White(), { 20, yOffset + 13 } );
        _renderQueue.addScreenRenderableText( "    Spawn: LCTRL or LB", Color::White(), { 20, yOffset + 26 } );
        _renderQueue.addScreenRenderableText( "Spawner B:", Color::White(), { 20, yOffset + 39 } );
        _renderQueue.addScreenRenderableText( "    Move: UP,DOWN,LEFT,RIGHT or R_STICK", Color::White(), { 20, yOffset + 52 } );
        _renderQueue.addScreenRenderableText( "    Spawn: RCTRL or RB", Color::White(), { 20, yOffset + 65 } );
    }
}