#pragma once

#include <engine/utils/position.h>
#include <engine/resources/renderable.h>

#include <engine/resources/resourcedefs.h>

#include <utils/geometry/shapes/shape.h>

namespace puma
{
    class EngineRenderer
    {
    public:

        void beginRender();
        void endRender();
        void render();

    private:
        void queueRenderables();
        void queueDebugRenderables();

        void queueRenderableCallback( AppTexture _texture, AppTextureSample _textureSample, RenderSize _renderSize, Position _position, float _rotation );

        std::vector<Renderable> m_renderables;  
    };
}