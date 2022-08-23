#pragma once
#include <modules/nina/ninadefinitions.h>
#include <engine/ecs/components/irendercomponent.h>
#include <internal/renderer/renderables/irenderable.h>

namespace puma
{

    class RenderComponent final : public IRenderComponent
    {
    public:

        void addTextureInfo( TextureInfo _textureInfo ) { m_textures.emplace_back( _textureInfo ); }

        const TextureInfoContainer& getTextureInfoContainer() const { return m_textures; }

    private:

        TextureInfoContainer m_textures;
    };
}