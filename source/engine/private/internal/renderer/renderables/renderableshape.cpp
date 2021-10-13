#include <precompiledengine.h>

#include "renderableshape.h"
#include <application/irenderer.h>
#include <internal/services/engineapplicationservice.h>

namespace puma
{
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

    void RenderableShape::render()
    {
        switch ( m_renderableShapeType )
        {
        case RenderableShapeType::RenderableCircle:
        {
            const RenderableCircle& circle = m_renderableShape.circle;
            if ( circle.solid )
            {
                gInternalEngineApplication->getRenderer()->renderSolidCircle( circle.center, circle.radius, m_color );
            }
            else
            {
                gInternalEngineApplication->getRenderer()->renderCircle( circle.center, circle.radius, m_color );
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
                gInternalEngineApplication->getRenderer()->renderSolidPolygon( screenPointsList, m_color );
            }
            else
            {
                gInternalEngineApplication->getRenderer()->renderPolygon( screenPointsList, m_color );
            }
            break;
        }
        case RenderableShapeType::RenderableChain:
        {
            const RenderableChain& chain = m_renderableShape.chain;

            for ( int pointIndex = 0; pointIndex < chain.points.size() - 1; ++pointIndex )
            {
                gInternalEngineApplication->getRenderer()->renderSegment( chain.points[pointIndex], chain.points[pointIndex + 1], m_color );
            }
            break;
        }
        default:
            assert( false ); //RenderableChapeType not supported
            break;
        }
    }

}