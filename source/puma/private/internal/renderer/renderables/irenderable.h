#pragma once

#include <engine/utils/position.h>
#include <engine/utils/renderdefinitions.h>
#include <nina/texturemanager/texture.h>
#include <nina/texturemanager/texturedefinitions.h>
#include <utils/graphics/dimensions.h>
#include <utils/genericid.h>

namespace puma
{
    class IRenderable
    {
    public:

        virtual ~IRenderable() {}

        virtual void render() const = 0;

        void setRenderLayer( RenderLayer _value ) { m_renderLayer = _value; }
        RenderLayer getRenderLayer() const { return m_renderLayer; }

    private:
        
        RenderLayer m_renderLayer = RenderLayer(0);
    };
}