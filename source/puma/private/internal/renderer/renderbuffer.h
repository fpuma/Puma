#pragma once

#include <engine/renderer/irenderqueue.h>

#include <internal/renderer/renderables/renderabletexture.h>
#include <internal/renderer/renderables/renderableshape.h>
#include <internal/renderer/renderables/renderabletext.h>

#include <utils/containers/containedvector.h>

namespace puma
{

    class RenderBuffer
    {
    public:

        RenderBuffer();

        void addRenderableTexture( const NinaTexture& _texture, const NinaTextureSample& _textureSample, const RenderSize& _renderSize, const Position& _position, const RotationDegrees& _rotation, RenderLayer _renderLayer, bool _debug );
        void addRenderableText( const std::string& _textToRender, const Color& _color, const Position& _position, RenderLayer _renderLayer, bool _debug );
        void addRenderableShape( const Shape& _shape, const Color& _color, bool _solid, const Position& _position, const RotationDegrees& _rotation, RenderLayer _renderLayer, bool _debug );
             
        void addScreenRenderableTexture( const NinaTexture& _texture, const NinaTextureSample& _textureSample, const Extent& _screenExtent, const RotationDegrees& _rotation, RenderLayer _renderLayer, bool _debug );
        void addScreenRenderableText( const std::string& _textToRender, const Color& _color, const ScreenPos& _screenPos, RenderLayer _renderLayer, bool _debug );

        void render();

        void sortByRenderLayer();

        void clear();

    private:

        void addRenderable( IRenderable* _renderable, bool _debug );

        std::vector<IRenderable*> m_renderables;
        std::vector<IRenderable*> m_debugRenderables;

        ContainedVector<RenderableTexture, kMaxRenderablesCount> m_textures;
        ContainedVector<RenderableText, kMaxRenderablesCount> m_texts;
        ContainedVector<RenderableShape, kMaxRenderablesCount> m_shapes;

    };
}