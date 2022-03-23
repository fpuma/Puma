#include <precompiledengine.h>

#include "engineapplication.h"

#include <application/iwindow.h>
#include <application/irenderer.h>

#include <input/iinput.h>

#include <logger/logger.h>
#include <logger/output/consolelogoutput.h>

#include <texturemanager/itexturemanager.h>

#ifdef _DEBUG
#include <engine/services/iprovidersservice.h>
#include <internal/ecs/base/providers/componentprovider.h>
#include <internal/ecs/components/cameracomponent.h>
#include <internal/ecs/components/locationcomponent.h>
#endif

namespace puma
{
    EngineApplication::EngineApplication()
    {
        m_application = nina::IApplication::create();
        m_application->getLogger()->addOutput<ConsoleLogOutput>();
    }

    void EngineApplication::init( Extent _windowExtent, const char* _windowName )
    {
        m_application->init();
        nina::WindowHandle windowHandle = m_application->createWindow( _windowExtent, _windowName );
        
        assert( windowHandle != nina::kInvalidWindowHandle );

        m_window = m_application->getWindow( windowHandle );
        if ( m_window->getRenderer()->isValid() )
        {
            m_renderer = m_window->getRenderer();
            m_textureManager = m_window->getRenderer()->getTextureManager();
        }

        m_input = NinaInput::create();
        m_input->init();
    }

    void EngineApplication::uninit()
    {
        m_input->uninit();
        if ( m_window->isValid() )
        {
            m_application->removeWindow( m_window->getWindowHandle() );
        }
        m_application->uninit();
    }
  
    void EngineApplication::setCameraEntity( Entity _cameraEntity )
    {
#ifdef _DEBUG
        ComponentProvider* componentProvider = gProviders->get<ComponentProvider>();
        CameraComponent* cameraComponent = componentProvider->get<CameraComponent>( _cameraEntity );
        LocationComponent* locationComponent = componentProvider->get<LocationComponent>( _cameraEntity );
        assert( (nullptr != cameraComponent) && (nullptr != locationComponent) );
#endif
        m_cameraEntity = _cameraEntity;
    }

    void EngineApplication::setWindowSize( s32 _width, s32 _height )
    {
        m_window->setWindowSize( _width, _height );
    }

    void EngineApplication::setWindowPosition( s32 _x, s32 _y )
    {
        m_window->setWindowPosition( _x, _y );
    }
}