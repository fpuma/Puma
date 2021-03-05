#pragma once
#include <engine/ecs/components/irendercomponent.h>
#include <engine/resources/renderable.h>
#include <engine/application/applicationdefinitions.h>

namespace puma
{

    class RenderComponent final : public IRenderComponent
    {
    public:

        void enable() override { m_enabled = true; };
        void disable() override { m_enabled = false; };
        bool isEnabled() const override { return m_enabled; }

        void addTextureInfo( TextureInfo _textureInfo ) { m_textures.emplace_back( _textureInfo ); }

        const TextureInfoContainer& getTextureInfoContainer() const { return m_textures; }

    private:

        Renderable  m_renderable;

        TextureInfoContainer m_textures;

        bool m_enabled = true;
    };
}