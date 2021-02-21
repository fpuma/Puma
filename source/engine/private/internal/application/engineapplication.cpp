#include <precompiledengine.h>

#include "engineapplication.h"

#include <internal/services/applicationservice.h>
#include <application/iwindow.h>
#include <application/irenderer.h>

namespace puma
{

    std::unique_ptr<IEngineApplication> IEngineApplication::create()
    {
        return std::make_unique<EngineApplication>();
    }

    EngineApplication::EngineApplication()
    {
        m_application = std::make_unique<app::IApplication>();
    }

    void EngineApplication::init( Extent _windowExtent, const char* _windowName )
    {
        app::WindowHandle windowHandle = m_application->createWindow( _windowExtent, _windowName );
        
        assert( windowHandle != app::kInvalidWindowHandle );

        m_window = m_application->getWindow( windowHandle );
        if ( m_window->getRenderer()->isValid() )
        {
            m_renderer = m_window->getRenderer();
            m_textureManager = m_window->getRenderer()->getTextureManager();
        }

        m_input = input::IInput::create();
        m_input->init();
    }

    void EngineApplication::uninit()
    {
        m_input->uninit();
        if ( m_window->isValid() )
        {
            m_application->removeWindow( m_window->getWindowHandle() );
        }
    }
  
}