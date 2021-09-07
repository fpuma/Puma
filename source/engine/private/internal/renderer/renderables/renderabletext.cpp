#include <precompiledengine.h>

#include "renderabletext.h"
#include <internal/services/engineapplicationservice.h>
#include <application/irenderer.h>

namespace puma
{
    void RenderableText::setText( const std::string& _text, const ScreenPos& _position, const Color& _color )
    {
        m_textToRender = _text;
        m_position = _position;
        m_textColor = _color;
    }

    void RenderableText::render()
    {
        gInternalEngineApplication->getRenderer()->renderText( m_position, m_textColor, m_textToRender.c_str() );
    }


}