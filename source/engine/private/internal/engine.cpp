#include <precompiledengine.h>
#include <internal/engine.h>

#include <internal/ecs/base/providers/componentprovider.h>
#include <internal/ecs/components/cameracomponent.h>
#include <internal/ecs/components/collisioncomponent.h>
#include <internal/ecs/components/locationcomponent.h>
#include <internal/ecs/components/rendercomponent.h>
#include <internal/services/base/servicecontainer.h>
#include <internal/services/inputservice.h>
#include <internal/services/graphicsservice.h>
#include <internal/services/physicsservice.h>
#include <internal/services/providersservice.h>
#include <internal/services/systemsservice.h>

#include <internal/ecs/base/providers/entityprovider.h>
#include <internal/ecs/systems/rendersystem.h>

#include <engine/utils/timerprovider.h>

#include <time/timestamp.h>

#include <application/irenderer.h>

#include <iostream>

#include <string>


namespace puma
{

    namespace
    {
        void registerServicesClasses()
        {
            gProviders->registerInterface<IEntityProvider, EntityProvider>();
            gProviders->registerInterface<IComponentProvider, ComponentProvider>();
            gProviders->registerClass<TimerProvider>( );

            gInternalSystems->registerInterface<IRenderSystem, RenderSystem>();
        }

        void registerComponents()
        {
            ComponentProvider* componentProvider = gProviders->get<ComponentProvider>();

            componentProvider->registerInterface<ICameraComponent, CameraComponent>();
            componentProvider->registerInterface<ICollisionComponent, CollisionComponent>();
            componentProvider->registerInterface<ILocationComponent, LocationComponent>();
            componentProvider->registerInterface<IRenderComponent, RenderComponent>();
        }
    }

    std::unique_ptr<IEngine> IEngine::create()
    {
        return std::make_unique<Engine>();
    }

    void Engine::init()
    {
        m_services = std::make_unique<ServiceContainer>();
        m_services->init();
        DefaultInstance<IServiceContainer>::setInstance( m_services.get() );
        
        registerServicesClasses();

        gInternalSystems->init();

        gProviders->add<EntityProvider>();
        gProviders->add<ComponentProvider>();
        gProviders->add<TimerProvider>();

        registerComponents();

        physics::WorldID worldId = gPhysics->addWorld( physics::Vec2{} );
        gPhysics->setDefaultWorld( worldId );

        RenderSystem* renderSystem = gInternalSystems->add<RenderSystem>();
        renderSystem->init();

        gInternalSystems->updateSystemsProperties();
    }

    void Engine::uninit()
    {
        m_services->uninit();
    }

    void Engine::update()
    {
        m_deltaTime.update();
        gInput->update();
        gApplication->update();
        m_shouldQuit = gApplication->shouldQuit();

        float currentDeltaTime = (float)m_deltaTime.get();
        gInternalSystems->update( currentDeltaTime );
        gInternalSystems->prePhysicsUpdate( currentDeltaTime );
        gPhysics->update( currentDeltaTime );
        gInternalSystems->postPhysicsUpdate( currentDeltaTime );
    }

    void Engine::render()
    {
        app::IRenderer* renderer = gApplication->getRenderer();
        renderer->beginRender();

        gInternalSystems->get<RenderSystem>()->render();

        renderer->renderText( 0, 0, std::to_string( 1.0f / m_deltaTime.getAverage() ).c_str() );
        //Timestamp ts;
        //ts.setToCurrentLocalTime();
        //renderer.renderText( ts.ToString().c_str() );

        renderer->endRender();
    }

}