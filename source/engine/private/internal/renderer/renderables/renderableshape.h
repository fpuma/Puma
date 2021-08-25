#pragma once

#include <internal/renderer/renderables/irenderable.h>
#include <utils/geometry/shapes/shape.h>

namespace puma
{
    class RenderableShape : public IRenderable
    {
    public:

        void setShape( const Shape& _shape, const Position& _position, const Color& _color )
        {
            m_shape = _shape;
            m_position = _position;
            m_color = _color;
        }

        void render() override {}

    private:

        Shape m_shape;
        Position m_position;
        Color m_color;
    };
}