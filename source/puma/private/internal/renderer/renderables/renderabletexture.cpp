#include <precompiledengine.h>

#include "renderabletexture.h"
#include <internal/services/engineapplicationservice.h>

#include <nina/application/irenderer.h>

namespace puma
{
    
    void RenderableTexture::setTexture( nina::Texture _texture, nina::TextureSample _textureSample )
    {
        m_texture = _texture;

        s32 lowerX = (s32)((float)m_texture.getOriginalSize().width * _textureSample.lowerLimit.u);
        s32 lowerY = (s32)((float)m_texture.getOriginalSize().height * _textureSample.lowerLimit.v);
        s32 upperX = (s32)((float)m_texture.getOriginalSize().width * _textureSample.upperLimit.u);
        s32 upperY = (s32)((float)m_texture.getOriginalSize().height * _textureSample.upperLimit.v);

        m_sampledExtent.xPos = lowerX;
        m_sampledExtent.yPos = lowerY;
        m_sampledExtent.width = upperX - lowerX;
        m_sampledExtent.height = upperY - lowerY;
    }

    void RenderableTexture::render() const
    {
        gInternalEngineApplication->getWindowRenderer()->renderTexture( m_texture,
            m_sampledExtent,
            m_screenExtent,
            m_rotationRadians);
    }


}