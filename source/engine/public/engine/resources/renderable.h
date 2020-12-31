#pragma once

#include <texturemanager/texture.h>
#include <texturemanager/texturedefinitions.h>
#include <utils/graphics/dimensions.h>

namespace puma
{
    class Renderable
    {
    public:

        void setTexture( app::Texture _texture ) { m_texture = _texture; }
        void setUVMap( app::TextureSample _uvMap ) { m_textureSample = _uvMap; }

        app::Texture getTexture() const { return m_texture; }
        Extent getUVExtent() const
        {
            Extent uvExtent;
            uvExtent.xPos = (s32)((float)m_texture.getOriginalSize().width * m_textureSample.lowerLimit.u); 
            uvExtent.yPos = (s32)((float)m_texture.getOriginalSize().height * m_textureSample.lowerLimit.v); 
            uvExtent.width = (s32)((float)m_texture.getOriginalSize().width * m_textureSample.upperLimit.u);
            uvExtent.height = (s32)((float)m_texture.getOriginalSize().height * m_textureSample.upperLimit.v);
            return uvExtent;
        }

    private:

        app::TextureSample m_textureSample;
        app::Texture m_texture;
    };
}