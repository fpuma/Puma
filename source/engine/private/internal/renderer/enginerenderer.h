#pragma once

#include <engine/utils/position.h>
#include <engine/resources/renderable.h>

#include <engine/resources/resourcedefs.h>

namespace puma
{
    class EngineRenderer
    {
    public:

        void render();

    private:
        void queueRenderables();
        void queueDebugRenderables();

        std::vector<Renderable> m_renderables;
    };
}