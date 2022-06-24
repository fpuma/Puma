#pragma once

#include <engine/renderer/irenderqueue.h>
#include <internal/renderer/renderbuffer.h>
#include <utils/multithreadbuffer.h>

namespace puma
{

    class RenderQueue : public IRenderQueue
    {
    public:

        RenderQueue();

        void startQueue();
        void endQueue();

        void addRenderableTexture( const nina::Texture& _texture, const nina::TextureSample& _textureSample, const RenderSize& _renderSize, const Position& _position, const RotationDegrees& _rotation, RenderLayer _renderLayer ) override;
        void addRenderableText( const std::string& _textToRender, const Color& _color, const Position& _position, RenderLayer _renderLayer ) override;
        void addRenderableShape( const Shape& _shape, const Color& _color, bool _solid, const Position& _position, const RotationDegrees& _rotation, RenderLayer _renderLayer ) override;

        void addScreenRenderableTexture( const nina::Texture& _texture, const nina::TextureSample& _textureSample, const Extent& _screenExtent, const RotationDegrees& _rotation, RenderLayer _renderLayer ) override;
        void addScreenRenderableText( const std::string& _textToRender, const Color& _color, const ScreenPos& _screenPos, RenderLayer _renderLayer ) override;

        void addDebugRenderableTexture( const nina::Texture& _texture, const nina::TextureSample& _textureSample, const RenderSize& _renderSize, const Position& _position, const RotationDegrees& _rotation, RenderLayer _renderLayer ) override;
        void addDebugRenderableText( const std::string& _textToRender, const Color& _color, const Position& _position, RenderLayer _renderLayer ) override;
        void addDebugRenderableShape( const Shape& _shape, const Color& _color, bool _solid, const Position& _position, const RotationDegrees& _rotation, RenderLayer _renderLayer ) override;

        void addDebugScreenRenderableTexture( const nina::Texture& _texture, const nina::TextureSample& _textureSample, const Extent& _screenExtent, const RotationDegrees& _rotation, RenderLayer _renderLayer ) override;
        void addDebugScreenRenderableText( const std::string& _textToRender, const Color& _color, const ScreenPos& _screenPos, RenderLayer _renderLayer ) override;

        void render();

    private:

        MultiThreadBuffer<RenderBuffer> m_renderBuffer;
    };
}