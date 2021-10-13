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

        RenderQueue();

        void addRenderableTexture( const AppTexture& _texture, const AppTextureSample& _textureSample, const RenderSize& _renderSize, const Position& _position, const RotationDegrees& _rotation ) override;
        void addRenderableText( const std::string& _textToRender, const Color& _color, const Position& _position ) override;
        void addRenderableShape( const Shape& _shape, const Color& _color, bool _solid, const Position& _position, const RotationDegrees& _rotation ) override;

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