#pragma once

#include <internal/renderer/renderables/irenderable.h>
#include <modules/nina/ninadefinitions.h>
#include <engine/utils/position.h>
#include <nina/texturemanager/texture.h>
#include <nina/texturemanager/texturedefinitions.h>
#include <utils/graphics/dimensions.h>

namespace puma
{
    class RenderableTexture : public IRenderable
    {
    public:

        void setTexture( nina::Texture _texture, nina::TextureSample _textureSample = {} );

        void setScreenExtent( Extent _screenExtent ) { m_screenExtent = _screenExtent; }
        void setRotationRadians( float _rotationRadians ) { m_rotationRadians = _rotationRadians; }

        nina::Texture getTexture() const { return m_texture; }
        Extent getSampledExtent() const { return m_sampledExtent; }
        Extent getScreenExtent() const { return m_screenExtent; }
        float getRotationRadians() const { return m_rotationRadians; }

        void render() const override;

    private:

        nina::Texture m_texture;
        Extent m_sampledExtent;
        Extent m_screenExtent = { 50,50,0,0 };
        float m_rotationRadians = 0.0f;
    };
}