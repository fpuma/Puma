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

        void queueRenderables();

    private:

        RenderQueue m_renderQueue;
    };
}