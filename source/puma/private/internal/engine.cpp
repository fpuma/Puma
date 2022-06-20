#include <precompiledengine.h>
#include <internal/engine.h>

#include <nina/application/irenderer.h>
#include <engine/utils/timerprovider.h>
#include <engine/igame.h>
#include <nina/input/iinput.h>

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
        
        /*
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
        InputSystem* inputSystem = gInternalSystems->add<InputSystem>();

        gInternalSystems->updateSystemsProperties();

        gInternalLogger->getLogger()->addOutput<ConsoleLogOutput>();

        gInternalLogger->info( "Puma engine initialized." );

        gInternalEngineApplication->init( _windowExtent, _windowName );
        inputSystem->registerInputListener();
    }

    void Engine::uninit()
    {
        gInternalSystems->get<InputSystem>()->unregisterInputListener();
        gInternalLogger->info( "Puma engine uninitializing." );
        m_services->uninit();
    }

    void Engine::simulationUpdate( IGame* _game )
    {
        m_deltaTime.update();

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
        m_appDt.update();

        gInternalSystems->get<InputSystem>()->updateWriteBuffer();
        gInternalEngineApplication->getInput()->update();

        gInternalEngineApplication->update();
        m_shouldQuit = gInternalEngineApplication->shouldQuit();
        render();
    }

    void Engine::render()
    {
        m_engineRenderer.beginRender();

        m_engineRenderer.render();

        //[fpuma] TODO check memory leak in the filledPolygonRGBA method from the sdl_gfx library
        //gInternalEngineApplication->getRenderer()->renderSolidPolygon( { {0,0}, {0,24}, {140,24}, {140,0} }, Color{ 0,0,0,255 } );
        gInternalEngineApplication->getRenderer()->renderText( ScreenPos{ 2, 2 },  {255,255,0,255}, formatString( "SIM: %.2f fps", 1.0f / m_deltaTime.getAverage() ).c_str() );
        gInternalEngineApplication->getRenderer()->renderText( ScreenPos{ 2, 14 }, {255,255,0,255}, formatString( "APP: %.2f fps", 1.0f / m_appDt.getAverage() ).c_str() );

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