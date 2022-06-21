#include <precompiledengine.h>

#include "renderqueue.h"

namespace puma
{
    RenderQueue::RenderQueue()
        : m_toRead( &m_buffer0 )
        , m_nextToRead( nullptr )
        , m_toWrite( &m_buffer1 )
        , m_nextToWrite( &m_buffer2 )
    {

    }

    void RenderQueue::startQueue()
    {
        m_toWrite->clear();
    }

    void RenderQueue::endQueue()
    {
        m_toWrite->sortByRenderLayer();
        std::lock_guard<std::mutex> guard( m_bufferSyncMutex );
        std::swap( m_nextToRead, m_toWrite );
        if(nullptr == m_toWrite)
        { 
            std::swap( m_toWrite, m_nextToWrite );
        }
    }

    void RenderQueue::addRenderableTexture( const NinaTexture& _texture, const NinaTextureSample& _textureSample, const RenderSize& _renderSize, const Position& _position, const RotationDegrees& _rotation, RenderLayer _renderLayer )
    {
        m_toWrite->addRenderableTexture( _texture, _textureSample, _renderSize, _position, _rotation, _renderLayer, false );
    }

    void RenderQueue::addRenderableText( const std::string& _textToRender, const Color& _color, const Position& _position, RenderLayer _renderLayer )
    {
        m_toWrite->addRenderableText( _textToRender, _color, _position, _renderLayer, false );
    }

    void RenderQueue::addRenderableShape( const Shape& _shape, const Color& _color, bool _solid, const Position& _position, const RotationDegrees& _rotation, RenderLayer _renderLayer )
    {
        m_toWrite->addRenderableShape( _shape, _color, _solid, _position, _rotation, _renderLayer, false );
    }

    void RenderQueue::addScreenRenderableTexture( const NinaTexture& _texture, const NinaTextureSample& _textureSample, const Extent& _screenExtent, const RotationDegrees& _rotation, RenderLayer _renderLayer )
    {
        m_toWrite->addScreenRenderableTexture( _texture, _textureSample, _screenExtent, _rotation, _renderLayer, false );
    }

    void RenderQueue::addScreenRenderableText( const std::string& _textToRender, const Color& _color, const ScreenPos& _screenPos, RenderLayer _renderLayer )
    {
        m_toWrite->addScreenRenderableText( _textToRender, _color, _screenPos, _renderLayer, false );
    }

    void RenderQueue::addDebugRenderableTexture( const NinaTexture& _texture, const NinaTextureSample& _textureSample, const RenderSize& _renderSize, const Position& _position, const RotationDegrees& _rotation, RenderLayer _renderLayer )
    {
        m_toWrite->addRenderableTexture( _texture, _textureSample, _renderSize, _position, _rotation, _renderLayer, true );
    }

    void RenderQueue::addDebugRenderableText( const std::string& _textToRender, const Color& _color, const Position& _position, RenderLayer _renderLayer )
    {
        m_toWrite->addRenderableText( _textToRender, _color, _position, _renderLayer, true );
    }

    void RenderQueue::addDebugRenderableShape( const Shape& _shape, const Color& _color, bool _solid, const Position& _position, const RotationDegrees& _rotation, RenderLayer _renderLayer )
    {
        m_toWrite->addRenderableShape( _shape, _color, _solid, _position, _rotation, _renderLayer, true );
    }

    void RenderQueue::addDebugScreenRenderableTexture( const NinaTexture& _texture, const NinaTextureSample& _textureSample, const Extent& _screenExtent, const RotationDegrees& _rotation, RenderLayer _renderLayer )
    {
        m_toWrite->addScreenRenderableTexture( _texture, _textureSample, _screenExtent, _rotation, _renderLayer, true );
    }

    void RenderQueue::addDebugScreenRenderableText( const std::string& _textToRender, const Color& _color, const ScreenPos& _screenPos, RenderLayer _renderLayer )
    {
        m_toWrite->addScreenRenderableText( _textToRender, _color, _screenPos, _renderLayer, true );
    }

    void RenderQueue::render()
    {
        m_toRead->render();
        std::lock_guard<std::mutex> guard( m_bufferSyncMutex );
        if (nullptr != m_nextToRead)
        {
            assert( nullptr == m_nextToWrite ); //If nextToRead is available, nextToWrite must be nullptr
            std::swap( m_toRead, m_nextToWrite );
            std::swap( m_toRead, m_nextToRead );
        }
    }
}