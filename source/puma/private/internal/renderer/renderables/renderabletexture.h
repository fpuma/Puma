#pragma once

#include <internal/renderer/renderables/irenderable.h>
#include <engine/external/ninadefinitions.h>
#include <engine/utils/position.h>
#include <nina/texturemanager/texture.h>
#include <nina/texturemanager/texturedefinitions.h>
#include <utils/graphics/dimensions.h>

namespace puma
{
    class RenderableTexture : public IRenderable
    {
    public:

        void setTexture( NinaTexture _texture, NinaTextureSample _textureSample = {} );

        void setScreenExtent( Extent _screenExtent ) { m_screenExtent = _screenExtent; }
        void setRotationDegrees( float _rotationDegrees ) { m_rotationDegrees = _rotationDegrees; }

        NinaTexture getTexture() const { return m_texture; }
        Extent getSampledExtent() const { return m_sampledExtent; }
        Extent getScreenExtent() const { return m_screenExtent; }
        float getRotationDegrees() const { return m_rotationDegrees; }

        void render() const override;

    private:

        NinaTexture m_texture;
        Extent m_sampledExtent;
        Extent m_screenExtent = { 50,50,0,0 };
        float m_rotationDegrees = 0.0f;
    };
}