#include <precompiledengine.h>

#include "test.h"


#include <data/collisionindexes.h>

#include <modules/pina/entity.h>
#include <engine/ecs/components/icameracomponent.h>
#include <engine/ecs/components/icollisioncomponent.h>
#include <engine/ecs/components/ilocationcomponent.h>
#include <engine/ecs/components/irendercomponent.h>
#include <engine/ecs/components/iinputcomponent.h>
#include <engine/ecs/systems/icollisionsystem.h>
#include <engine/ecs/systems/irendersystem.h>
#include <engine/ecs/systems/iinputsystem.h>
#include <modules/leo/leodefinitions.h>
#include <modules/nina/ninadefinitions.h>

#include <engine/services/iengineapplicationservice.h>
#include <engine/services/iloggerservice.h>
#include <engine/services/ecsservice.h>

#include <utils/graphics/dimensions.h>
#include <utils/formatstring.h>

#include <test/systems/ballspawnersystem.h>
#include <test/systems/staticstuffsystem.h>
#include <test/components/movedirectioncomponent.h>
#include <data/spawners/floorspawner.h>
#include <data/inputactions.h>

namespace test
{

    namespace
    {
        puma::Entity MyDefaultCamera;
        puma::Entity Floor0;
        puma::Entity Floor1;
        puma::Entity Floor2;
        puma::Entity Floor3;
        puma::Entity FloorController;

        puma::ContainedVector<Entity, 4> FloorList;

        puma::Entity buildDefaultCamera()
        {
            puma::EntityProvider* entityProvider = gEntities;
            puma::ComponentProvider* componentProvider = gComponents;

            puma::Entity result = entityProvider->requestEntity();
            auto locationComponent = componentProvider->addComponent<puma::ILocationComponent>( result );
            auto cameraComponent = componentProvider->addComponent<puma::ICameraComponent>( result );

            locationComponent->setPosition( { 0.0f, 0.0f } );
            cameraComponent->setMetersPerPixel( 0.2f );

            return result;
        }

        void destroyDefaultCamera( puma::Entity _entity )
        {
            puma::EntityProvider* entityProvider = gEntities;
            puma::ComponentProvider* componentProvider = gComponents;

            componentProvider->removeComponent<puma::ICameraComponent>( _entity );
            componentProvider->removeComponent<puma::ILocationComponent>( _entity );

            entityProvider->disposeEntity( _entity );
        }

    }

    void setCamera();
    void initPhysics();

    void setCamera()
    {
        MyDefaultCamera = buildDefaultCamera();
        gEngineApplication->setCameraEntity( MyDefaultCamera );
    }

    void Test::init()
    {
        gEngineApplication->setWindowSize( 500, 500 );
        gEngineApplication->setWindowPosition( 100, 100 );

        initPhysics();
        setCamera();

        SystemProvider* sysProvider = gSystems;

        //Register components
        gComponents->registerComponent<MoveDirectionComponent>();

        //Register systems
        sysProvider->registerSystem<BallSpawnerSystem>();
        auto ballSpawnerSystem = sysProvider->addSystem<BallSpawnerSystem>();
        assert( nullptr != ballSpawnerSystem );

        sysProvider->registerSystem<StaticStuffSystem>();
        auto staticStuffSystem = sysProvider->addSystem<StaticStuffSystem>();
        assert( nullptr != staticStuffSystem );

        //Init systems
        ballSpawnerSystem->init();
        staticStuffSystem->init();

        //Spawn
        Floor0 = spawnFloor( gEngineApplication->getTextureManager(), { 15.0f, -15.0f, 0.0f }, 45.0f );
        Floor1 = spawnFloor( gEngineApplication->getTextureManager(), { -15.0f, -15.0f, 0.0f }, -45.0f );

        Floor2 = spawnFloor( gEngineApplication->getTextureManager(), { 15.0f, 15.0f, 0.0f }, -45.0f );
        Floor3 = spawnFloor( gEngineApplication->getTextureManager(), { -15.0f, 15.0f, 0.0f }, 45.0f );

        FloorList.push_back( Floor0 );
        FloorList.push_back( Floor1 );
        FloorList.push_back( Floor2 );
        FloorList.push_back( Floor3 );

        //Floor controller
        FloorController = gEntities->requestEntity();

        puma::IInputComponent* ic = gComponents->addComponent<IInputComponent>( FloorController ).get();
        ic->addInputMap( TestInputActions::ToggleFloorEntity, { puma::nina::KeyboardKey::KB_I, puma::InputModifier_IGNORE, puma::nina::InputButtonEvent::Pressed } );
        ic->addInputMap( TestInputActions::ToggleFloorPhysics, { puma::nina::KeyboardKey::KB_K, puma::InputModifier_IGNORE, puma::nina::InputButtonEvent::Pressed } );

        gSystems->getSystem<IInputSystem>()->registerEntity( FloorController );

        //[fpuma] TODO Loading all assets now to prevent a race condition later.
        // I need to create a ResourceManager that supports multithreading
        auto textureManager = gEngineApplication->getTextureManager();
        textureManager->loadTexture( "../assets/green.png" );
        textureManager->loadTexture( "../assets/bricks.jpg" );
        textureManager->loadTexture( "../assets/tennisball.png" );

        sysProvider->subscribeSystemUpdate<StaticStuffSystem>( SystemUpdateId::QueueRenderables );
        sysProvider->subscribeSystemUpdate<BallSpawnerSystem>( SystemUpdateId::QueueRenderables );
        sysProvider->subscribeSystemUpdate<BallSpawnerSystem>( SystemUpdateId::Update );
    }

    void Test::update( float _deltaTime )
    {
        puma::ComponentProvider* cp = gComponents;
        puma::EntityProvider* ep = gEntities;
        
        puma::IInputComponent* inputComp = cp->getComponent<IInputComponent>( FloorController );
        bool toggleFloorEntity = inputComp->isActionActive( TestInputActions::ToggleFloorEntity );
        bool toggleFloorPhysics = inputComp->isActionActive( TestInputActions::ToggleFloorPhysics );


        if (toggleFloorEntity)
        {
            if (ep->isEntityEnabled( Floor2 ))
            {
                ep->disableEntity( Floor2 );
            }
            else
            {
                ep->enableEntity( Floor2 );
            }
        }

        if (toggleFloorPhysics)
        {
            puma::ICollisionComponent* colComp = cp->getComponent<ICollisionComponent>( Floor2 );

            if (colComp->isEnabled())
            {
                colComp->disable();
            }
            else
            {
                colComp->enable();
            }
        }
    }

    void Test::uninit()
    {
        destroyDefaultCamera( MyDefaultCamera );

        unspawnFloor( Floor0 );
        unspawnFloor( Floor1 );
        unspawnFloor( Floor2 );
        unspawnFloor( Floor3 );

        SystemProvider* sysProvider = gSystems;

        sysProvider->unsubscribeSystemUpdate<StaticStuffSystem>( SystemUpdateId::QueueRenderables );
        sysProvider->unsubscribeSystemUpdate<BallSpawnerSystem>( SystemUpdateId::QueueRenderables );
        sysProvider->unsubscribeSystemUpdate<BallSpawnerSystem>( SystemUpdateId::Update );

        gSystems->getSystem<StaticStuffSystem>()->uninit();
        gSystems->getSystem <BallSpawnerSystem>()->uninit();

        gSystems->getSystem<IInputSystem>()->unregisterEntity( FloorController );
        gComponents->removeComponent<IInputComponent>( FloorController );
        gEntities->disposeEntity( FloorController );
    }

    void initPhysics()
    {
        auto collisitonSystemPtr = gSystems->getSystem<puma::ICollisionSystem>();
        collisitonSystemPtr->init( { 0.0f, -10.0f } );
        collisitonSystemPtr->setCollisionCompatibility( kCollisionCompatibility );
    }
}
