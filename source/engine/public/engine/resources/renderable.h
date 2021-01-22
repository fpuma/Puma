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

        void setTexture( app::Texture _texture, app::TextureSample _textureSample = {} )
        { 
            m_texture = _texture; 

            m_sampledExtent.xPos =   (s32)((float)m_texture.getOriginalSize().width  * _textureSample.lowerLimit.u);
            m_sampledExtent.yPos =   (s32)((float)m_texture.getOriginalSize().height * _textureSample.lowerLimit.v);
            m_sampledExtent.width =  (s32)((float)m_texture.getOriginalSize().width  * _textureSample.upperLimit.u);
            m_sampledExtent.height = (s32)((float)m_texture.getOriginalSize().height * _textureSample.upperLimit.v);
        }
        void setRenderSize( RenderSize _renderSize ) { m_renderSize = _renderSize; }

        app::Texture getTexture() const { return m_texture; }
        RenderSize getRenderSize() const { return m_renderSize; }
        Extent getSampledExtent() const { return m_sampledExtent; }

    private:

        app::Texture m_texture;
        Extent m_sampledExtent;
        RenderSize m_renderSize;
    };
}