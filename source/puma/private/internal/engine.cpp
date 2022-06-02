#include <precompiledengine.h>
#include <internal/engine.h>

#include <application/irenderer.h>
#include <engine/utils/timerprovider.h>
#include <engine/igame.h>
#include <input/iinput.h>

#include <internal/ecs/base/providers/componentprovider.h>
#include <internal/ecs/base/providers/entityprovider.h>
#include <internal/ecs/components/cameracomponent.h>
#include <internal/ecs/components/collisioncomponent.h>
#include <internal/ecs/components/inputcomponent.h>
#include <internal/ecs/components/locationcomponent.h>
#include <internal/ecs/components/rendercomponent.h>
#include <internal/ecs/systems/collisionsystem.h>
#include <internal/ecs/systems/rendersystem.h>
#include <internal/ecs/systems/inputsystem.h>
#include <internal/services/base/servicecontainer.h>
#include <internal/services/engineapplicationservice.h>
#include <internal/services/loggerservice.h>
#include <internal/services/physicsservice.h>
#include <internal/services/providersservice.h>
#include <internal/services/systemsservice.h>

#include <logger/output/consolelogoutput.h>

#include <time/timestamp.h>

namespace puma
{
    namespace
    {
        void registerServices()
        {
            gProviders->registerInterface<IEntityProvider, EntityProvider>();
            gProviders->registerInterface<IComponentProvider, ComponentProvider>();
            gProviders->registerClass<TimerProvider>( );
        }

        void registerSystems()
        {
            gInternalSystems->registerInterface<IRenderSystem, RenderSystem>();
            gInternalSystems->registerInterface<ICollisionSystem, CollisionSystem>();
            gInternalSystems->registerInterface<IInputSystem, InputSystem>();
        }

        void registerComponents()
        {
            ComponentProvider* componentProvider = gProviders->get<ComponentProvider>();

            componentProvider->registerInterface<ICameraComponent, CameraComponent>();
            componentProvider->registerInterface<ICollisionComponent, CollisionComponent>();
            componentProvider->registerInterface<ILocationComponent, LocationComponent>();
            componentProvider->registerInterface<IRenderComponent, RenderComponent>();
            componentProvider->registerInterface<IInputComponent, InputComponent>();
        }
    }

    void IEngine::run( std::unique_ptr<IGame>&& _game )
    {
        std::unique_ptr<Engine> engine = std::make_unique<Engine>();

        engine->init();
        _game->init();
        
        //*
        while (!engine->shouldQuit())
        {
            engine->simulationUpdate( _game.get() );
            engine->applicationUpdate();
        }
        /*/
        std::thread ut( [&]() { engine->updateThread( _game.get() ); } );
        
        while (!engine->shouldQuit())
        {
            engine->applicationUpdate();
        }

        ut.join();
        //*/


        _game->uninit();
        engine->uninit();
    }

    void Engine::init( const Extent _windowExtent, const char* _windowName )
    {
        m_services = std::make_unique<ServiceContainer>();
        m_services->init();
        DefaultInstance<IServiceContainer>::setInstance( m_services.get() );
        
        registerServices();
        registerSystems();

        gProviders->add<EntityProvider>();
        gProviders->add<ComponentProvider>();
        gProviders->add<TimerProvider>();

        registerComponents();

        gInternalSystems->add<RenderSystem>();
        gInternalSystems->add<CollisionSystem>();
        gInternalSystems->add<InputSystem>();

        gInternalSystems->updateSystemsProperties();

        gInternalLogger->getLogger()->addOutput<ConsoleLogOutput>();

        gInternalLogger->info( "Puma engine initialized." );

        gInternalEngineApplication->init( _windowExtent, _windowName );
    }

    void Engine::uninit()
    {
        gInternalLogger->info( "Puma engine uninitializing." );
        m_services->uninit();
    }

    void Engine::simulationUpdate( IGame* _game )
    {
        m_deltaTime.update();

        if (m_shouldQuit)
        {
            return;
        }

        float currentDeltaTime = static_cast<float>(m_deltaTime.get());
        gInternalSystems->update( currentDeltaTime );
        gInternalSystems->prePhysicsUpdate( currentDeltaTime );
        gPhysics->update( currentDeltaTime );
        gInternalSystems->postPhysicsUpdate( currentDeltaTime );
        _game->update(currentDeltaTime);
        m_engineRenderer.queueRenderables();
    }

    void Engine::applicationUpdate()
    {
        gInternalEngineApplication->getInput()->update();

        gInternalEngineApplication->update();
        m_shouldQuit = gInternalEngineApplication->shouldQuit();
        render();
    }

    void Engine::render()
    {
        if ( m_shouldQuit )
        {
            return;
        }

        m_engineRenderer.beginRender();

        m_engineRenderer.render();

        gInternalEngineApplication->getRenderer()->renderText( ScreenPos{ 0, 0 }, Color{255,0,255,255}, std::to_string( 1.0f / m_deltaTime.getAverage() ).c_str() );

        m_engineRenderer.endRender();
    }

    void Engine::updateThread( IGame* _game )
    {
        while (!shouldQuit())
        {
            simulationUpdate( _game );
        }
    }
}