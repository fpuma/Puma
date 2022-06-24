#include <precompiledengine.h>

#include "enginerenderer.h"

#include <nina/application/irenderer.h>

#include <engine/services/iprovidersservice.h>

#include <internal/ecs/base/providers/componentprovider.h>
#include <internal/ecs/components/cameracomponent.h>
#include <internal/ecs/components/locationcomponent.h>
#include <internal/services/systemsservice.h>
#include <internal/services/engineapplicationservice.h>


namespace puma
{
    void EngineRenderer::beginRender()
    {
        gInternalEngineApplication->getWindowRenderer()->beginRender();
    }

    void EngineRenderer::endRender()
    {
        gInternalEngineApplication->getWindowRenderer()->endRender();
    }

    void EngineRenderer::render()
    {
        m_renderQueue.render();
    }

    void EngineRenderer::queueRenderables()
    {
        m_renderQueue.startQueue();
        gInternalSystems->queueRenderables( m_renderQueue );
        m_renderQueue.endQueue();
    }
}