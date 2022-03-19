#pragma once

#include <engine/renderer/irenderqueue.h>

#include <internal/renderer/renderables/renderabletexture.h>
#include <internal/renderer/renderables/renderableshape.h>
#include <internal/renderer/renderables/renderabletext.h>

namespace puma
{
    class RenderQueue : public IRenderQueue
    {
    public:

        RenderQueue();

        void addRenderableTexture( const NinaTexture& _texture, const NinaTextureSample& _textureSample, const RenderSize& _renderSize, const Position& _position, const RotationDegrees& _rotation, RenderLayer _renderLayer, bool _debug = false ) override;
        void addRenderableText( const std::string& _textToRender, const Color& _color, const Position& _position, RenderLayer _renderLayer, bool _debug = false ) override;
        void addRenderableShape( const Shape& _shape, const Color& _color, bool _solid, const Position& _position, const RotationDegrees& _rotation, RenderLayer _renderLayer, bool _debug = false ) override;

        void addScreenRenderableTexture( const NinaTexture& _texture, const NinaTextureSample& _textureSample, const Extent& _screenExtent, const RotationDegrees& _rotation, RenderLayer _renderLayer, bool _debug = false ) override;
        void addScreenRenderableText( const std::string& _textToRender, const Color& _color, const ScreenPos& _screenPos, RenderLayer _renderLayer, bool _debug = false ) override;

        void sortByRenderLayer();

        void render();

        void clear();

    private:

        void addRenderable( IRenderable* _renderable, bool _debug );

        std::vector<IRenderable*> m_renderables;
        std::vector<IRenderable*> m_debugRenderables;

        u32 m_renderableTexturesCount = 0;
        std::array<RenderableTexture, kMaxRenderablesCount> m_textures;

        u32 m_renderableTextsCount = 0;
        std::array<RenderableText, kMaxRenderablesCount> m_texts;

        u32 m_renderableShapesCount = 0;
        std::array<RenderableShape, kMaxRenderablesCount> m_shapes;

    };
}