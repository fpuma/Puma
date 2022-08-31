#pragma once

#include <engine/utils/renderdefinitions.h>
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
        bool solid = false;
    };

    struct RenderablePolygon
    {
        ShapeScreenPointsList vertices;
        bool solid = false;
    };


    class RenderableShape : public IRenderable
    {
    public:

        void fromWorldShape( const Shape& _shape, const Color& _color, bool _solid, const Position& _position, const RotationRadians& _rotation );

        void setAsCircle( s32 _radius, const ScreenPos& _center, const Color& _color, bool _solid );
        void setAsChain( const ShapeScreenPointsList& _points, const Color& _color );
        void setAsPolygon( const ShapeScreenPointsList& _vertices, const Color& _color, bool _solid );

        bool shouldRender() const { return m_shouldRender; }

        void render() const override;

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
        bool m_shouldRender = false;
    };
}