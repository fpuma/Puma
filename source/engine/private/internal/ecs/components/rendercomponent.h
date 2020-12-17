#pragma once
#include <engine/ecs/components/irendercomponent.h>
#include <engine/resources/renderable.h>

namespace puma
{
    class RenderComponent final : public IRenderComponent
    {
    public:

        void enable() override { m_enabled = true; };
        void disable() override { m_enabled = false; };
        bool isEnabled() const override { return m_enabled; }

        void setSize( const RenderSize& _size ) override { m_size = _size; }
        RenderSize getSize() const override { return m_size; }
        
        app::Texture getTexture() const override { return m_renderable.getTexture(); }
        app::Extent getUVExtent() const override { return m_renderable.getUVExtent(); }

        void setRenderable( const Renderable& _renderable ) override { m_renderable = _renderable; }

    private:

        RenderSize m_size;
        Renderable  m_renderable;
        bool m_enabled = true;
    };
}