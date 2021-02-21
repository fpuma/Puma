#include <precompiledengine.h>

#include "enginerenderer.h"

#include <internal/services/systemsservice.h>

namespace puma
{
    void EngineRenderer::render()
    {
        queueRenderables();
        queueDebugRenderables();

    }

    void EngineRenderer::queueRenderables()
    {
        RenderablesBackInserter backInserter = std::back_inserter( m_renderables );

        gInternalSystems->queueRenderables( backInserter );
    }

    void EngineRenderer::queueDebugRenderables()
    {
        RenderablesBackInserter backInserter = std::back_inserter( m_renderables );

        gInternalSystems->queueDebugRenderables( backInserter );
    }
}