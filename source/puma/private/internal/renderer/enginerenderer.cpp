#include <precompiledengine.h>

#include "enginerenderer.h"

#include <application/irenderer.h>

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
        gInternalEngineApplication->getRenderer()->beginRender();
    }

    void EngineRenderer::endRender()
    {
        gInternalEngineApplication->getRenderer()->endRender();
    }

    void EngineRenderer::render()
    {
        m_renderQueue.clear();
        queueRenderables();
        m_renderQueue.render();
    }

    void EngineRenderer::queueRenderables()
    {
        gInternalSystems->queueRenderables( m_renderQueue );
        m_renderQueue.sortByRenderLayer();
    }
}