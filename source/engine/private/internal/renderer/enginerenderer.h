#pragma once

#include <engine/utils/position.h>
#include <engine/utils/renderdefinitions.h>
#include <internal/renderer/renderable.h>
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

        void queueRenderableCallback( AppTexture _texture, AppTextureSample _textureSample, RenderSize _renderSize, Position _position, float _rotation );

        std::vector<Renderable> m_renderables;  
    };
}