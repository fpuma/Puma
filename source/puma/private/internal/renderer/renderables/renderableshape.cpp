#include <precompiledengine.h>

#include "renderableshape.h"
#include <nina/application/irenderer.h>
#include <internal/renderer/enginerendererhelpers.h>
#include <internal/services/engineapplicationservice.h>
#include <utils/geometry/geometryhelpers.h>

namespace puma
{

    void RenderableShape::fromWorldShape( const Shape& _shape, const Color& _color, bool _solid, const Position& _position, const RotationRadians& _rotation )
    {
        Vec2 flattenedPos = { _position.x, _position.y };
        Rectangle frustum; 
        float metersPerPixel = 0.0f;
        erh::getCameraInfo( frustum, metersPerPixel );

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
                ShapeScreenPointsList screenChain;

                std::transform( newChain.points.begin(), newChain.points.end(), std::back_inserter( screenChain ), [&]( const Vec2& chainPoint )
                {
                    return erh::worldPointToScreen( chainPoint, frustum, metersPerPixel );
                } );

                setAsChain( screenChain, _color );
                m_shouldRender = true;
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
                ScreenPos centerScreenPos = erh::worldPointToScreen( circleWorldPosition, frustum, metersPerPixel );
                s32 radiusInPixels = (s32)(circle.radius / metersPerPixel);

                setAsCircle( radiusInPixels, centerScreenPos, _color, _solid );
                m_shouldRender = true;
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
                ShapeScreenPointsList screenPolygon;

                std::transform( newPolygon.vertices.begin(), newPolygon.vertices.end(), std::back_inserter( screenPolygon ), [&]( const Vec2& polygonPoint )
                {
                    return erh::worldPointToScreen( polygonPoint, frustum, metersPerPixel );
                } );

                setAsPolygon( screenPolygon, _color, _solid );
                m_shouldRender = true;
            }
            break;
        }
        default:
            assert( false ); //Unsupported shape type.
            break;
        }
    }

    void RenderableShape::setAsCircle( s32 _radius, const ScreenPos& _center, const Color& _color, bool _solid )
    {
        RenderableCircle circle;
        
        m_renderableShape.circle.center = _center;
        m_renderableShape.circle.radius = _radius;
        m_renderableShape.circle.solid = _solid;

        m_renderableShapeType = RenderableShapeType::RenderableCircle;
        
        m_color = _color;
    }

    void RenderableShape::setAsChain( const ShapeScreenPointsList& _points, const Color& _color )
    {
        m_renderableShape.chain.points = _points;

        m_renderableShapeType = RenderableShapeType::RenderableChain;

        m_color = _color;
    }

    void RenderableShape::setAsPolygon( const ShapeScreenPointsList& _vertices, const Color& _color, bool _solid )
    {
        m_renderableShape.polygon.vertices = _vertices;
        m_renderableShape.polygon.solid = _solid;

        m_renderableShapeType = RenderableShapeType::RenderablePolygon;

        m_color = _color;
    }

    void RenderableShape::render() const
    {
        switch ( m_renderableShapeType )
        {
        case RenderableShapeType::RenderableCircle:
        {
            const RenderableCircle& circle = m_renderableShape.circle;
            if ( circle.solid )
            {
                gInternalEngineApplication->getWindowRenderer()->renderSolidCircle( circle.center, circle.radius, m_color );
            }
            else
            {
                gInternalEngineApplication->getWindowRenderer()->renderCircle( circle.center, circle.radius, m_color );
            }
            break;
        }
        case RenderableShapeType::RenderablePolygon:
        {
            const RenderablePolygon& polygon = m_renderableShape.polygon;

            std::vector<ScreenPos> screenPointsList;

            screenPointsList.assign( polygon.vertices.begin(), polygon.vertices.end() );

            if ( polygon.solid )
            {
                gInternalEngineApplication->getWindowRenderer()->renderSolidPolygon( screenPointsList, m_color );
            }
            else
            {
                gInternalEngineApplication->getWindowRenderer()->renderPolygon( screenPointsList, m_color );
            }
            break;
        }
        case RenderableShapeType::RenderableChain:
        {
            const RenderableChain& chain = m_renderableShape.chain;

            for ( int pointIndex = 0; pointIndex < chain.points.size() - 1; ++pointIndex )
            {
                gInternalEngineApplication->getWindowRenderer()->renderSegment( chain.points[pointIndex], chain.points[pointIndex + 1], m_color );
            }
            break;
        }
        default:
            assert( false ); //RenderableChapeType not supported
            break;
        }
    }

}