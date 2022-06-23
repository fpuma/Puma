#pragma once

#include <internal/renderer/renderables/irenderable.h>

namespace puma
{
    class RenderableText : public IRenderable
    {
    public:

        void setText( const std::string& _text, const ScreenPos& _position, const Color& _color );

        void render() const override;

    private:

        std::string m_textToRender;
        Color m_textColor;
        ScreenPos m_position;

    };
}