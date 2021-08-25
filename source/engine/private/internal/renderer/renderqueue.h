#pragma once

#include <engine/renderer/irenderqueue.h>

#include <internal/renderer/renderables/renderabletexture.h>
#include <internal/renderer/renderables/renderableshape.h>
#include <internal/renderer/renderables/renderabletext.h>

namespace puma
{
    constexpr int kMaxRenderablesCount = 100;

    class RenderQueue : public IRenderQueue
    {
    public:

        void addRenderableTexture( AppTexture _texture, AppTextureSample _textureSample, RenderSize _renderSize, Position _position, RotationDegrees _rotation ) override;
        void addRenderableText() override {}
        void addRenderableShape() override {}

        void render();

        void clear();

    private:

        std::vector<IRenderable*> m_renderables;

        u32 m_renderableTexturesCount = 0;
        std::array<RenderableTexture, kMaxRenderablesCount> m_textures;

        u32 m_renderableTextsCount = 0;
        std::array<RenderableText, kMaxRenderablesCount> m_texts;

        u32 m_renderableShapesCount = 0;
        std::array<RenderableShape, kMaxRenderablesCount> m_shapes;

    };
}