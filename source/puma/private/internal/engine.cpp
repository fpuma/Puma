#include <precompiledengine.h>
#include <internal/engine.h>

#include <nina/application/irenderer.h>
#include <engine/utils/timerprovider.h>
#include <engine/igame.h>
#include <nina/input/iinput.h>

#include <engine/services/ecsservice.h>
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


#include <logger/output/consolelogoutput.h>

#include <time/timestamp.h>

namespace puma
{
    namespace
    {

        void registerSystems()
        {
            gSystems->registerSystem<IRenderSystem, RenderSystem>();
            gSystems->registerSystem<ICollisionSystem, CollisionSystem>();
            gSystems->registerSystem<IInputSystem, InputSystem>();
        }

        void registerComponents()
        {
            ComponentProvider* componentProvider = gComponents;

            componentProvider->registerComponent<ICameraComponent, CameraComponent>();
            componentProvider->registerComponent<ICollisionComponent, CollisionComponent>();
            componentProvider->registerComponent<ILocationComponent, LocationComponent>();
            componentProvider->registerComponent<IRenderComponent, RenderComponent>();
            componentProvider->registerComponent<IInputComponent, InputComponent>();
        }

        void initSystems()
        {
            gSystems->addSystem<RenderSystem>();
            gSystems->addSystem<CollisionSystem>();
            auto inputSystem = gSystems->addSystem<InputSystem>();
            inputSystem->registerInputListener();


            gSystems->subscribeSystemUpdate<RenderSystem>( SystemUpdateId::QueueRenderables );
            gSystems->subscribeSystemUpdate<InputSystem>( SystemUpdateId::Update );
            gSystems->subscribeSystemUpdate<CollisionSystem>( SystemUpdateId::PostPhysics );
            gSystems->subscribeSystemUpdate<CollisionSystem>( SystemUpdateId::QueueRenderables );
        }

        void uninitSystems()
        {
            gSystems->unsubscribeSystemUpdate<RenderSystem>( SystemUpdateId::QueueRenderables );
            gSystems->unsubscribeSystemUpdate<InputSystem>( SystemUpdateId::Update );
            gSystems->unsubscribeSystemUpdate<CollisionSystem>( SystemUpdateId::PostPhysics );
            gSystems->unsubscribeSystemUpdate<CollisionSystem>( SystemUpdateId::QueueRenderables );

            SystemProvider* systemProvider = gSystems;
            InputSystem* inputSystem = systemProvider->getSystem<InputSystem>();
            inputSystem->unregisterInputListener();
            inputSystem->uninit();
            systemProvider->getSystem<CollisionSystem>()->uninit();
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
        
        gInternalEngineApplication->init( _windowExtent, _windowName );

        gInternalLogger->getLogger()->addOutput<ConsoleLogOutput>();
        gInternalLogger->info( "Puma engine initializing." );

        registerSystems();
        registerComponents();

        initSystems();

        gInternalLogger->info( "Puma engine initialized." );
    }

    void Engine::uninit()
    {
        gInternalLogger->info( "Puma engine uninitializing." );

        uninitSystems();
        
        gInternalLogger->info( "Puma engine uninitialized." );
        m_services->uninit();
    }

    void Engine::simulationUpdate( IGame* _game )
    {
        m_deltaTime.update();

        float currentDeltaTime = static_cast<float>(m_deltaTime.get());
        gSystems->update( *gEntities, *gComponents );
        gSystems->prePhysicsUpdate( *gEntities, *gComponents );
        gPhysics->update( currentDeltaTime );
        gSystems->postPhysicsUpdate( *gEntities, *gComponents );
        _game->update(currentDeltaTime);
        m_engineRenderer.queueRenderables();
    }

    void Engine::applicationUpdate()
    {
        m_appDt.update();

        gSystems->getSystem<InputSystem>()->updateWriteBuffer();
        gInternalEngineApplication->getInput()->update();

        gInternalEngineApplication->update();
        m_shouldQuit = gInternalEngineApplication->shouldQuit();
        render();
    }

    void Engine::render()
    {
        m_engineRenderer.beginRender();

        m_engineRenderer.render();

        gInternalEngineApplication->getWindowRenderer()->renderSolidPolygon( { {0,0}, {0,24}, {140,24}, {140,0} }, Color{ 0,0,0,255 } );
        gInternalEngineApplication->getWindowRenderer()->renderText( ScreenPos{ 2, 2 },  {255,255,0,255}, formatString( "SIM: %.2f fps", 1.0f / m_deltaTime.getAverage() ).c_str() );
        gInternalEngineApplication->getWindowRenderer()->renderText( ScreenPos{ 2, 14 }, {255,255,0,255}, formatString( "APP: %.2f fps", 1.0f / m_appDt.getAverage() ).c_str() );

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