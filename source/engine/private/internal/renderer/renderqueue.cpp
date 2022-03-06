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

    void RenderQueue::addRenderableTexture( const AppTexture& _texture, const AppTextureSample& _textureSample, const RenderSize& _renderSize, const Position& _position, const RotationDegrees& _rotation, bool _debug /*= false*/ )
    {
        Rectangle frustum;
        float metersPerPixel;
        erh::getCameraInfo( frustum, metersPerPixel );

        Rectangle boundingBox = erh::getAABB( _position, _renderSize );

        if ( erh::shouldRender( boundingBox, frustum ) )
        {
            RenderableTexture& renderable = m_textures[m_renderableTexturesCount];
            renderable.setTexture( _texture, _textureSample );
            renderable.setRotationDegrees( -_rotation );

            Extent screenExtent;

            screenExtent.xPos = (s32)((boundingBox.lowerBoundary.x - frustum.lowerBoundary.x) / metersPerPixel);
            screenExtent.yPos = (s32)((frustum.upperBoundary.y - boundingBox.upperBoundary.y) / metersPerPixel);
            screenExtent.width = (s32)(_renderSize.x / metersPerPixel);
            screenExtent.height = (s32)(_renderSize.y / metersPerPixel);

            renderable.setScreenExtent( std::move( screenExtent ) );

            m_renderables.emplace_back( &renderable );

            ++m_renderableTexturesCount;
        }
    }

    void RenderQueue::addRenderableText( const std::string& _textToRender, const Color& _color, const Position& _position, bool _debug /*= false*/ )
    {
        Rectangle frustum;
        float metersPerPixel;
        erh::getCameraInfo( frustum, metersPerPixel );

        bool isInFrustum =  frustum.upperBoundary.x > _position.x &&
                            frustum.upperBoundary.y > _position.y &&
                            frustum.lowerBoundary.x < _position.x &&
                            frustum.lowerBoundary.y < _position.y;

        if ( isInFrustum )
        {
            RenderableText& renderable = m_texts[m_renderableTextsCount];
            ScreenPos screenPosition = erh::worldPointToScreen(_position, frustum, metersPerPixel);
            renderable.setText(_textToRender, screenPosition, _color);

            addRenderable( &renderable, _debug );

            ++m_renderableTextsCount;
        }
    }
    
    void RenderQueue::addRenderableShape( const Shape& _shape, const Color& _color, bool _solid, const Position& _position, const RotationDegrees& _rotation, bool _debug /*= false*/ )
    {
        Rectangle frustum;
        float metersPerPixel;
        erh::getCameraInfo( frustum, metersPerPixel );
        Vec2 flattenedPos = { _position.x, _position.y };

        switch ( _shape.getShapeType() )
        {
        case ShapeType::Chain:
        {
            const Chain& chain = _shape.getAsChain();

            Chain newChain;

            std::transform( chain.points.begin(), chain.points.end(), std::back_inserter( newChain.points ), [&]( const Vec2& point )
            {
                Vec2 newPoint = GeometryHelpers::rotatePoint2D( point, _rotation );
                newPoint = newPoint + flattenedPos;
                return newPoint;
            } );

            if ( erh::shouldRender( newChain.points, frustum ) )
            {
                RenderableShape& renderable = m_shapes[m_renderableShapesCount];
                ShapeScreenPointsList screenChain;

                std::transform( newChain.points.begin(), newChain.points.end(), std::back_inserter( screenChain ), [&]( const Vec2& chainPoint )
                {
                    return erh::worldPointToScreen( chainPoint, frustum, metersPerPixel );
                } );

                renderable.setAsChain( screenChain, _color);
                addRenderable( &renderable, _debug );
                ++m_renderableShapesCount;
            }

            break;
        }
        case ShapeType::Circle:
        {
            Circle circle = _shape.getAsCircle();

            Vec2 circleWorldPosition = circle.center + flattenedPos;
            Vec2 upperBoundOffset = { circle.radius, circle.radius };
            Vec2 lowerBoundOffset = { -circle.radius, -circle.radius };

            Rectangle circleAABB = { upperBoundOffset, lowerBoundOffset };

            if ( erh::shouldRender( circleAABB, frustum ) )
            {
                RenderableShape& renderable = m_shapes[m_renderableShapesCount];

                ScreenPos centerScreenPos = erh::worldPointToScreen( circleWorldPosition, frustum, metersPerPixel );
                s32 radiusInPixels = (s32)(circle.radius / metersPerPixel);

                renderable.setAsCircle( radiusInPixels, centerScreenPos, _color, _solid );

                addRenderable( &renderable, _debug );
                ++m_renderableShapesCount;
            }

            break;
        }
        case ShapeType::Polygon:
        {
            Polygon polygon = _shape.getAsPolygon();

            Polygon newPolygon;

            std::transform( polygon.vertices.begin(), polygon.vertices.end(), std::back_inserter( newPolygon.vertices ), [&]( const Vec2& point )
            {
                Vec2 newPoint = GeometryHelpers::rotatePoint2D( point, _rotation );
                newPoint = newPoint + flattenedPos;
                return newPoint;
            } );

            if ( erh::shouldRender( newPolygon.vertices, frustum ) )
            {
                RenderableShape& renderable = m_shapes[m_renderableShapesCount];
                ShapeScreenPointsList screenPolygon;

                std::transform( newPolygon.vertices.begin(), newPolygon.vertices.end(), std::back_inserter( screenPolygon ), [&]( const Vec2& polygonPoint )
                {
                    return erh::worldPointToScreen( polygonPoint, frustum, metersPerPixel );
                } );

                renderable.setAsPolygon( screenPolygon, _color, _solid );
                addRenderable( &renderable, _debug );
                ++m_renderableShapesCount;
            }
            break;
        }
        default:
            assert( false ); //Unsupported shape type.
            break;
        }
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