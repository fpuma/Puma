#pragma once

#include <engine/services/igraphicsservice.h>

namespace puma
{
    class GraphicsService final : public IGraphicsService
    {
    public:
        
        GraphicsService() { m_graphics = gfx::IGraphics::create(); }

        ~GraphicsService() { m_graphics.reset(); }

        gfx::IGraphics* get() override { return m_graphics.get(); }

        void uninit() { m_graphics->uninit(); }

    private:

        std::unique_ptr<gfx::IGraphics> m_graphics;
    };

}