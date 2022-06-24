#include <precompiledengine.h>

#include "renderqueue.h"

namespace puma
{
    RenderQueue::RenderQueue()
    {

    }

    void RenderQueue::startQueue()
    {
        m_renderBuffer.write()->clear();
    }

    void RenderQueue::endQueue()
    {
        m_renderBuffer.write()->sortByRenderLayer();
        m_renderBuffer.updateWriteBuffer( true );
    }

    void RenderQueue::addRenderableTexture( const nina::Texture& _texture, const nina::TextureSample& _textureSample, const RenderSize& _renderSize, const Position& _position, const RotationDegrees& _rotation, RenderLayer _renderLayer )
    {
        m_renderBuffer.write()->addRenderableTexture( _texture, _textureSample, _renderSize, _position, _rotation, _renderLayer, false );
    }

    void RenderQueue::addRenderableText( const std::string& _textToRender, const Color& _color, const Position& _position, RenderLayer _renderLayer )
    {
        m_renderBuffer.write()->addRenderableText( _textToRender, _color, _position, _renderLayer, false );
    }

    void RenderQueue::addRenderableShape( const Shape& _shape, const Color& _color, bool _solid, const Position& _position, const RotationDegrees& _rotation, RenderLayer _renderLayer )
    {
        m_renderBuffer.write()->addRenderableShape( _shape, _color, _solid, _position, _rotation, _renderLayer, false );
    }

    void RenderQueue::addScreenRenderableTexture( const nina::Texture& _texture, const nina::TextureSample& _textureSample, const Extent& _screenExtent, const RotationDegrees& _rotation, RenderLayer _renderLayer )
    {
        m_renderBuffer.write()->addScreenRenderableTexture( _texture, _textureSample, _screenExtent, _rotation, _renderLayer, false );
    }

    void RenderQueue::addScreenRenderableText( const std::string& _textToRender, const Color& _color, const ScreenPos& _screenPos, RenderLayer _renderLayer )
    {
        m_renderBuffer.write()->addScreenRenderableText( _textToRender, _color, _screenPos, _renderLayer, false );
    }

    void RenderQueue::addDebugRenderableTexture( const nina::Texture& _texture, const nina::TextureSample& _textureSample, const RenderSize& _renderSize, const Position& _position, const RotationDegrees& _rotation, RenderLayer _renderLayer )
    {
        m_renderBuffer.write()->addRenderableTexture( _texture, _textureSample, _renderSize, _position, _rotation, _renderLayer, true );
    }

    void RenderQueue::addDebugRenderableText( const std::string& _textToRender, const Color& _color, const Position& _position, RenderLayer _renderLayer )
    {
        m_renderBuffer.write()->addRenderableText( _textToRender, _color, _position, _renderLayer, true );
    }

    void RenderQueue::addDebugRenderableShape( const Shape& _shape, const Color& _color, bool _solid, const Position& _position, const RotationDegrees& _rotation, RenderLayer _renderLayer )
    {
        m_renderBuffer.write()->addRenderableShape( _shape, _color, _solid, _position, _rotation, _renderLayer, true );
    }

    void RenderQueue::addDebugScreenRenderableTexture( const nina::Texture& _texture, const nina::TextureSample& _textureSample, const Extent& _screenExtent, const RotationDegrees& _rotation, RenderLayer _renderLayer )
    {
        m_renderBuffer.write()->addScreenRenderableTexture( _texture, _textureSample, _screenExtent, _rotation, _renderLayer, true );
    }

    void RenderQueue::addDebugScreenRenderableText( const std::string& _textToRender, const Color& _color, const ScreenPos& _screenPos, RenderLayer _renderLayer )
    {
        m_renderBuffer.write()->addScreenRenderableText(_textToRender, _color, _screenPos, _renderLayer, true);
    }

    void RenderQueue::render()
    {
        m_renderBuffer.updateReadBuffer();
        m_renderBuffer.read()->render();
    }
}