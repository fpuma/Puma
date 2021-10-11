#pragma once

#include <internal/renderer/renderables/irenderable.h>
#include <utils/geometry/shapes/shape.h>
#include <utils/containers/containedvector.h>

namespace puma
{
    

    enum class RenderableShapeType
    {
        RenderableChain,
        RenderableCircle,
        RenderablePolygon,
    };

    struct RenderableChain
    {
        ShapeScreenPointsList points;
    };

    struct RenderableCircle
    {
        s32 radius;
        ScreenPos center;
    };

    struct RenderablePolygon
    {
        ShapeScreenPointsList vertices;
    };


    class RenderableShape : public IRenderable
    {
    public:

        void setAsCircle( s32 _radius, const ScreenPos& _center, const Color& _color );
        void setAsChain( const ShapeScreenPointsList& _points, const Color& _color );
        void setAsPolygon( const ShapeScreenPointsList& _vertices, const Color& _color );

        void render() override;

    private:

        union InternalRenderableShape
        {
            InternalRenderableShape() {}
            ~InternalRenderableShape() {}
            RenderableCircle circle = {};
            RenderableChain chain;
            RenderablePolygon polygon;
        }m_renderableShape;

        RenderableShapeType m_renderableShapeType = RenderableShapeType::RenderableCircle;
        ScreenPos m_position;
        Color m_color;
    };
}