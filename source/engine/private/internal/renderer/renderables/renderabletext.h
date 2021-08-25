#pragma once

#include <internal/renderer/renderables/irenderable.h>

namespace puma
{
    class RenderableText : public IRenderable
    {
    public:

        void setText( const std::string& _text, const Position& _position, const Color& _color )
        {
            m_textToRender = _text;
            m_position = _position;
            m_textColor = _color;
        }

        void render() override {}

    private:

        std::string m_textToRender;
        Color m_textColor;
        Position m_position;

    };
}