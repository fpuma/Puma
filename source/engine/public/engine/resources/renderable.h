#pragma once

#include <graphics/texture.h>

namespace puma
{
    class Renderable
    {
    public:

        void setTexture( gfx::Texture _texture ) { m_texture = _texture; }
        void setUVMap( gfx::TextureSample _uvMap ) { m_textureSample = _uvMap; }

        gfx::Texture getTexture() const { return m_texture; }
        gfx::Extent getUVExtent() const
        {
            gfx::Extent uvExtent;
            uvExtent.xPos = (s32)((float)m_texture.getOriginalSize().width * m_textureSample.upperLimit.u);
            uvExtent.yPos = (s32)((float)m_texture.getOriginalSize().height * m_textureSample.upperLimit.v);
            uvExtent.width = (s32)((float)m_texture.getOriginalSize().width * m_textureSample.lowerLimit.u);
            uvExtent.height = (s32)((float)m_texture.getOriginalSize().height * m_textureSample.lowerLimit.v);
            return uvExtent;
        }

    private:

        gfx::TextureSample m_textureSample;
        gfx::Texture m_texture;
    };
}