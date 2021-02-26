#include <precompiledengine.h>

#include "engineapplication.h"

#include <application/iwindow.h>
#include <application/irenderer.h>

#ifdef _DEBUG
#include <engine/services/iprovidersservice.h>
#include <internal/ecs/base/providers/componentprovider.h>
#include <internal/ecs/components/cameracomponent.h>
#include <internal/ecs/components/locationcomponent.h>
#endif

namespace puma
{

    std::unique_ptr<IEngineApplication> IEngineApplication::create()
    {
        return std::make_unique<EngineApplication>();
    }

    EngineApplication::EngineApplication()
    {
        m_application = app::IApplication::create();
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
}