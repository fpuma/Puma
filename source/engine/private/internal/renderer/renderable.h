#pragma once

#include <engine/utils/position.h>
#include <texturemanager/texture.h>
#include <texturemanager/texturedefinitions.h>
#include <utils/graphics/dimensions.h>

namespace puma
{


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

        void setScreenExtent( Extent _screenExtent ) { m_screenExtent = _screenExtent; }
        void setRotationDegrees( float _rotationDegrees ) { m_rotationDegrees = _rotationDegrees; }

        app::Texture getTexture() const  { return m_texture; }
        Extent getSampledExtent() const  { return m_sampledExtent; }
        Extent getScreenExtent() const   { return m_screenExtent; }
        float getRotationDegrees() const { return m_rotationDegrees; }

    private:

        app::Texture m_texture;
        Extent m_sampledExtent;
        Extent m_screenExtent;
        float m_rotationDegrees = 0.0f;
    };
}