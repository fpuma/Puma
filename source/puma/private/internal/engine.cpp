#include <precompiledengine.h>
#include <internal/engine.h>

#include <nina/application/irenderer.h>
#include <nina/input/iinput.h>
#include <engine/utils/timerprovider.h>
#include <engine/igame.h>

#include <engine/services/ecsservice.h>
#include <engine/services/systemsservice.h>
#include <internal/ecs/components/cameracomponent.h>
#include <internal/ecs/components/collisioncomponent.h>
#include <internal/ecs/components/inputcomponent.h>
#include <internal/ecs/components/locationcomponent.h>
#include <internal/ecs/components/rendercomponent.h>
#include <internal/ecs/systems/collisionsystem.h>
#include <internal/ecs/systems/rendersystem.h>
#include <internal/ecs/systems/inputsystem.h>
#include <internal/physics/collisionlistener.h>
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
            SystemProvider* systemProvider = gSystems;

            systemProvider->registerInterface<IRenderSystem, RenderSystem>();
            systemProvider->registerInterface<ICollisionSystem, CollisionSystem>();
            systemProvider->registerInterface<IInputSystem, InputSystem>();
        }

        void registerComponents()
        {
            pina::ComponentProvider* componentProvider = gComponents;

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
        
        gInternalEngineApplication->init( _windowExtent, _windowName );

        gPhysics->setSimulationTimeStep( m_simulationMinStep );

        gInternalLogger->getLogger()->addOutput<ConsoleLogOutput>();
        gInternalLogger->info( "Puma engine initializing." );

        registerSystems();
        registerComponents();

        gInternalLogger->info( "Puma engine initialized." );

        m_appDt.reset();
        m_innerDt.reset();
        m_outterDt.reset();
    }

    void Engine::uninit()
    {
        gInternalLogger->info( "Puma engine uninitializing..." );
        m_services->uninit();
    }

    void Engine::simulationUpdate( IGame* _game )
    {
        m_outterDt.update();
        float currentDeltaTime = static_cast<float>(m_outterDt.get());

        m_accumDeltaTime += currentDeltaTime;

        if (m_accumDeltaTime > m_simulationMinStep)
        {
            gSystems->update( *gEntities, *gComponents );
            gSystems->prePhysicsUpdate( *gEntities, *gComponents );
            gPhysics->update( m_accumDeltaTime );
            gSystems->postPhysicsUpdate( *gEntities, *gComponents );
            _game->update( m_accumDeltaTime );
            m_engineRenderer.queueRenderables();

            m_innerDt.update();

            m_accumDeltaTime = 0.0f;
        }
    }

    void Engine::applicationUpdate()
    {
        m_appDt.update();

        gSystems->get<InputSystem>()->updateWriteBuffer();
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
        gInternalEngineApplication->getWindowRenderer()->renderText( ScreenPos{ 2, 2 }, { 255,255,0,255 }, formatString( "SIM: %.2f fps", 1.0f / m_innerDt.getAverage() ).c_str() );
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