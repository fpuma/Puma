#pragma once

#include <texturemanager/texture.h>
#include <texturemanager/texturedefinitions.h>
#include <utils/graphics/dimensions.h>

namespace puma
{
    struct RenderSize
    {
        float x = 0.0f;
        float y = 0.0f;
    };

    class Renderable
    {
    public:

        void setTexture( app::Texture _texture ) { m_texture = _texture; }
        void setTextureSample( app::TextureSample _textureSample ) { m_textureSample = _textureSample; }
        void setRenderSize( RenderSize _renderSize ) { m_renderSize = _renderSize; }

        app::Texture getTexture() const { return m_texture; }
        RenderSize getRenderSize() const { return m_renderSize; }
        Extent getSampledExtent() const
        {
            Extent uvExtent;
            uvExtent.xPos = (s32)((float)m_texture.getOriginalSize().width * m_textureSample.lowerLimit.u); 
            uvExtent.yPos = (s32)((float)m_texture.getOriginalSize().height * m_textureSample.lowerLimit.v); 
            uvExtent.width = (s32)((float)m_texture.getOriginalSize().width * m_textureSample.upperLimit.u);
            uvExtent.height = (s32)((float)m_texture.getOriginalSize().height * m_textureSample.upperLimit.v);
            return uvExtent;
        }

    private:

        app::Texture m_texture;
        app::TextureSample m_textureSample;
        RenderSize m_renderSize;
    };
}