#pragma once

#include <engine/services/igraphicsservice.h>

namespace puma
{
    class GraphicsService final : public IGraphicsService
    {
    public:
        
        GraphicsService() { m_graphics = app::IApplication::create(); }

        ~GraphicsService() { m_graphics.reset(); }

        app::IApplication* get() override { return m_graphics.get(); }

        void uninit() { m_graphics->uninit(); }

    private:

        std::unique_ptr<app::IApplication> m_graphics;
    };

}