#include <precompiledengine.h>

#include "renderqueue.h"
#include "enginerendererhelpers.h"

namespace puma
{
    RenderQueue::RenderQueue()
    {
        m_renderables.reserve( kMaxRenderablesCount * 3 );
        m_debugRenderables.reserve( kMaxRenderablesCount * 3 );
    }

    void RenderQueue::addRenderableTexture( const NinaTexture& _texture, const NinaTextureSample& _textureSample, const RenderSize& _renderSize, const Position& _position, const RotationDegrees& _rotation, RenderLayer _renderLayer, bool _debug /*= false*/ )
    {
        Rectangle frustum;
        float metersPerPixel;
        erh::getCameraInfo( frustum, metersPerPixel );

        Rectangle boundingBox = erh::getAABB( _position, _renderSize );

        Extent screenExtent;

        screenExtent.xPos = (s32)((boundingBox.lowerBoundary.x - frustum.lowerBoundary.x) / metersPerPixel);
        screenExtent.yPos = (s32)((frustum.upperBoundary.y - boundingBox.upperBoundary.y) / metersPerPixel);
        screenExtent.width = (s32)(_renderSize.x / metersPerPixel);
        screenExtent.height = (s32)(_renderSize.y / metersPerPixel);

        if ( erh::shouldRender( boundingBox, frustum ) )
        {
            addScreenRenderableTexture( _texture, _textureSample, screenExtent, _rotation, _renderLayer, _debug );
        }
    }

    void RenderQueue::addRenderableText( const std::string& _textToRender, const Color& _color, const Position& _position, RenderLayer _renderLayer, bool _debug /*= false*/ )
    {
        Rectangle frustum;
        float metersPerPixel;
        erh::getCameraInfo( frustum, metersPerPixel );

        bool isInFrustum =  frustum.upperBoundary.x > _position.x &&
                            frustum.upperBoundary.y > _position.y &&
                            frustum.lowerBoundary.x < _position.x &&
                            frustum.lowerBoundary.y < _position.y;
        
        ScreenPos screenPosition = erh::worldPointToScreen(_position, frustum, metersPerPixel);

        if ( isInFrustum )
        {
            addScreenRenderableText( _textToRender, _color, screenPosition, _renderLayer, _debug );
        }
    }
    
    void RenderQueue::addRenderableShape( const Shape& _shape, const Color& _color, bool _solid, const Position& _position, const RotationDegrees& _rotation, RenderLayer _renderLayer, bool _debug /*= false*/ )
    {
        Rectangle frustum;
        float metersPerPixel;
        erh::getCameraInfo( frustum, metersPerPixel );
        Vec2 flattenedPos = { _position.x, _position.y };

        RenderableShape renderableShape;
        renderableShape.fromWorldShape( _shape, _color, _solid, _position, _rotation );

        if ( renderableShape.shouldRender() )
        {
            renderableShape.setRenderLayer( _renderLayer );
            m_shapes[m_renderableShapesCount] = renderableShape;
            addRenderable( &m_shapes[m_renderableShapesCount], _debug );
            ++m_renderableShapesCount;
        }
    }

    void RenderQueue::addScreenRenderableTexture( const NinaTexture& _texture, const NinaTextureSample& _textureSample, const Extent& _screenExtent, const RotationDegrees& _rotation, RenderLayer _renderLayer, bool _debug /*= false*/ )
    {
        RenderableTexture& renderable = m_textures[m_renderableTexturesCount];
        renderable.setRenderLayer( _renderLayer );
        renderable.setTexture( _texture, _textureSample );
        renderable.setRotationDegrees( -_rotation );

        renderable.setScreenExtent( std::move( _screenExtent ) );

        addRenderable( &renderable, _debug );

        ++m_renderableTexturesCount;
    }
    
    void RenderQueue::addScreenRenderableText( const std::string& _textToRender, const Color& _color, const ScreenPos& _screenPos, RenderLayer _renderLayer, bool _debug /*= false*/ )
    {
        RenderableText& renderable = m_texts[m_renderableTextsCount];
        renderable.setRenderLayer( _renderLayer );
        renderable.setText( _textToRender, _screenPos, _color );

        addRenderable( &renderable, _debug );

        ++m_renderableTextsCount;
    }
    
    void RenderQueue::sortByRenderLayer()
    {
        std::sort( m_renderables.begin(), m_renderables.end(), []( const IRenderable* renderable0, const IRenderable* renderable1 )
        {
            return renderable0->getRenderLayer() < renderable1->getRenderLayer();
        } );
    }

    void RenderQueue::render()
    {
        for ( IRenderable* renderable : m_renderables )
        {
            renderable->render();
        }

        for ( IRenderable* renderable : m_debugRenderables )
        {
            renderable->render();
        }
    }

    void RenderQueue::clear()
    {
        m_renderables.clear();
        m_debugRenderables.clear();
        m_renderableTexturesCount = 0;
        m_renderableTextsCount = 0;
        m_renderableShapesCount = 0;
    }

    void RenderQueue::addRenderable( IRenderable* _renderable, bool _debug )
    {
        if ( _debug )
        {
            m_debugRenderables.emplace_back( _renderable );
        }
        else
        {
            m_renderables.emplace_back( _renderable );
        }
    }
}