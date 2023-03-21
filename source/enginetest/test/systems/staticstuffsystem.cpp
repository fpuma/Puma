#include "precompiledengine.h"
#include "staticstuffsystem.h"

#include <data/inputactions.h>
#include <data/spawners/backgroundspawner.h>
#include <engine/services/iengineapplicationservice.h>
#include <engine/renderer/irenderqueue.h>
#include <engine/services/ecsservice.h>
#include <engine/services/systemsservice.h>
#include <engine/ecs/components/iinputcomponent.h>
#include <engine/renderer/renderhelpers.h>
#include <utils/formatstring.h>


namespace test
{
    StaticStuffSystem::StaticStuffSystem()
    {
    }

    void StaticStuffSystem::onInit()
    {
        gSystems->subscribeSystemUpdate<StaticStuffSystem>( SystemUpdateId::QueueRenderables );

        m_backgroundEntity = spawnBackground( gEngineApplication->getTextureManager(), { 0.0f, 0.0f } );
    }

    void StaticStuffSystem::onUninit()
    {
        gSystems->unsubscribeSystemUpdate<StaticStuffSystem>( SystemUpdateId::QueueRenderables );

        unspawnBackground( m_backgroundEntity );
    }

    void StaticStuffSystem::queueRenderables( IRenderQueue& _renderQueue )
    {
        auto inputComponent = gComponents->get<IInputComponent>( m_backgroundEntity );

        if (inputComponent->isActionActive( TestInputActions::MouseMove ))
        {
            InputActionExtraInfo extraInfo = inputComponent->getInputActionExtraInfo( TestInputActions::MouseMove );

            m_screenPos.xCoord = static_cast<s32>(extraInfo.x);
            m_screenPos.yCoord = static_cast<s32>(extraInfo.y);

            m_worldPosition = erh::screenPointToWorld( m_screenPos );
        }

        _renderQueue.addScreenRenderableText( formatString("ScreenPos: %d | %d ", m_screenPos.xCoord, m_screenPos.yCoord).c_str(), Color::White(), {20, 360});
        _renderQueue.addScreenRenderableText( formatString( "WorldPos: %.2f | %.2f ", m_worldPosition.x, m_worldPosition.y ).c_str(), Color::White(), { 20, 373 } );


        int yOffset = 400;
        _renderQueue.addScreenRenderableText( "Spawner A:", Color::White(), { 20, yOffset } );
        _renderQueue.addScreenRenderableText( "    Move: W,S,A,D or L_STICK", Color::White(), { 20, yOffset + 13 } );
        _renderQueue.addScreenRenderableText( "    Spawn: LCTRL or LB", Color::White(), { 20, yOffset + 26 } );
        _renderQueue.addScreenRenderableText( "Spawner B:", Color::White(), { 20, yOffset + 39 } );
        _renderQueue.addScreenRenderableText( "    Move: UP,DOWN,LEFT,RIGHT or R_STICK", Color::White(), { 20, yOffset + 52 } );
        _renderQueue.addScreenRenderableText( "    Spawn: RCTRL or RB", Color::White(), { 20, yOffset + 65 } );
        _renderQueue.addScreenRenderableText( "Toggle Floor: I | Toggle Floor Physics: K", Color::White(), { 20, yOffset + 78 } );
    }
}