#pragma once

#include <engine/utils/position.h>
#include <engine/utils/renderdefinitions.h>
#include <internal/renderer/renderables/irenderable.h>
#include <internal/renderer/renderqueue.h>


namespace puma
{
    
    class EngineRenderer
    {
    public:

        void beginRender();
        void endRender();
        void render();

    private:

        void queueRenderables();

        RenderQueue m_renderQueue;
    };
}