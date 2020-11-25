#pragma once

#include <graphics/texture.h>

namespace puma
{
    class Renderable
    {
    public:

        void setTexture( gfx::Texture _texture ) { m_texture = _texture; }
        void setUVMap( gfx::QuadUVMap _uvMap ) { m_uvMap = _uvMap; }

        gfx::Texture getTexture() const { return m_texture; }
        gfx::Extent getUVExtent() const
        {
            gfx::Extent uvExtent;
            uvExtent.xPos = (s32)((float)m_texture.getOriginalSize().width * m_uvMap.upperLeft.u);
            uvExtent.yPos = (s32)((float)m_texture.getOriginalSize().height * m_uvMap.upperLeft.v);
            uvExtent.width = (s32)((float)m_texture.getOriginalSize().width * m_uvMap.lowerRight.u);
            uvExtent.height = (s32)((float)m_texture.getOriginalSize().height * m_uvMap.lowerRight.v);
            return uvExtent;
        }

    private:

        gfx::QuadUVMap m_uvMap;
        gfx::Texture m_texture;
    };
}