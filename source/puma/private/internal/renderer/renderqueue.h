#pragma once

#include <engine/renderer/irenderqueue.h>
#include <internal/renderer/renderbuffer.h>
#include <mutex>

namespace puma
{

    class RenderQueue : public IRenderQueue
    {
    public:

        RenderQueue();

        void startQueue();
        void endQueue();

        void addRenderableTexture( const NinaTexture& _texture, const NinaTextureSample& _textureSample, const RenderSize& _renderSize, const Position& _position, const RotationDegrees& _rotation, RenderLayer _renderLayer ) override;
        void addRenderableText( const std::string& _textToRender, const Color& _color, const Position& _position, RenderLayer _renderLayer ) override;
        void addRenderableShape( const Shape& _shape, const Color& _color, bool _solid, const Position& _position, const RotationDegrees& _rotation, RenderLayer _renderLayer ) override;

        void addScreenRenderableTexture( const NinaTexture& _texture, const NinaTextureSample& _textureSample, const Extent& _screenExtent, const RotationDegrees& _rotation, RenderLayer _renderLayer ) override;
        void addScreenRenderableText( const std::string& _textToRender, const Color& _color, const ScreenPos& _screenPos, RenderLayer _renderLayer ) override;

        void addDebugRenderableTexture( const NinaTexture& _texture, const NinaTextureSample& _textureSample, const RenderSize& _renderSize, const Position& _position, const RotationDegrees& _rotation, RenderLayer _renderLayer ) override;
        void addDebugRenderableText( const std::string& _textToRender, const Color& _color, const Position& _position, RenderLayer _renderLayer ) override;
        void addDebugRenderableShape( const Shape& _shape, const Color& _color, bool _solid, const Position& _position, const RotationDegrees& _rotation, RenderLayer _renderLayer ) override;

        void addDebugScreenRenderableTexture( const NinaTexture& _texture, const NinaTextureSample& _textureSample, const Extent& _screenExtent, const RotationDegrees& _rotation, RenderLayer _renderLayer ) override;
        void addDebugScreenRenderableText( const std::string& _textToRender, const Color& _color, const ScreenPos& _screenPos, RenderLayer _renderLayer ) override;

        void render();

    private:

        RenderBuffer* m_toRead = nullptr;
        RenderBuffer* m_nextToRead = nullptr;
        RenderBuffer* m_toWrite = nullptr;
        RenderBuffer* m_nextToWrite = nullptr;

        RenderBuffer m_buffer0;
        RenderBuffer m_buffer1;
        RenderBuffer m_buffer2;

        std::mutex m_bufferSyncMutex;
    };
}