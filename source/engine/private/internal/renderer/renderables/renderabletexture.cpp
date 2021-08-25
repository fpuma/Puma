#pragma once
#include <precompiledengine.h>

#include "renderabletexture.h"
#include <internal/services/engineapplicationservice.h>

#include <application/irenderer.h>

namespace puma
{
    
    void RenderableTexture::setTexture( app::Texture _texture, app::TextureSample _textureSample )
    {
        m_texture = _texture;

        m_sampledExtent.xPos = (s32)((float)m_texture.getOriginalSize().width * _textureSample.lowerLimit.u);
        m_sampledExtent.yPos = (s32)((float)m_texture.getOriginalSize().height * _textureSample.lowerLimit.v);
        m_sampledExtent.width = (s32)((float)m_texture.getOriginalSize().width * _textureSample.upperLimit.u);
        m_sampledExtent.height = (s32)((float)m_texture.getOriginalSize().height * _textureSample.upperLimit.v);
    }

    void RenderableTexture::render()
    {
        gInternalEngineApplication->getRenderer()->renderTexture( m_texture,
            m_sampledExtent,
            m_screenExtent,
            m_rotationDegrees);
    }


}