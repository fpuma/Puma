#include <precompiledengine.h>

#include "test.h"


#include <data/collisionindexes.h>

#include <pina/entity.h>
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
#include <engine/services/systemsservice.h>

#include <utils/graphics/dimensions.h>
#include <utils/formatstring.h>
#include <utils/geometry/geometryhelpers.h>

#include <test/systems/ballspawnersystem.h>
#include <test/systems/staticstuffsystem.h>
#include <test/components/movedirectioncomponent.h>
#include <data/spawners/floorspawner.h>
#include <data/inputactions.h>

namespace test
{

    namespace
    {
        puma::pina::Entity MyDefaultCamera;
        puma::pina::Entity Floor0;
        puma::pina::Entity Floor1;
        puma::pina::Entity Floor2;
        puma::pina::Entity Floor3;
        puma::pina::Entity FloorController;

        puma::ContainedVector<pina::Entity, 4> FloorList;

        puma::pina::Entity buildDefaultCamera()
        {
            puma::pina::EntityProvider* entityProvider = gEntities;
            puma::pina::ComponentProvider* componentProvider = gComponents;

            puma::pina::Entity result = entityProvider->requestEntity();
            auto locationComponent = componentProvider->add<puma::ILocationComponent>( result );
            auto cameraComponent = componentProvider->add<puma::ICameraComponent>( result );

            locationComponent->setPosition( { 0.0f, 0.0f } );
            cameraComponent->setMetersPerPixel( 0.2f );

            return result;
        }

        void destroyDefaultCamera( puma::pina::Entity _entity )
        {
            puma::pina::EntityProvider* entityProvider = gEntities;
            puma::pina::ComponentProvider* componentProvider = gComponents;

            componentProvider->remove<puma::ICameraComponent>( _entity );
            componentProvider->remove<puma::ILocationComponent>( _entity );

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

        SystemProvider* sysProvider = gSystems;

        sysProvider->add<IInputSystem>();
        sysProvider->add<IRenderSystem>();
        sysProvider->add<ICollisionSystem>();

        initPhysics();
        setCamera();

        //Register components
        gComponents->registerClass<MoveDirectionComponent>();

        //Register systems
        sysProvider->registerClass<BallSpawnerSystem>();
        auto ballSpawnerSystem = sysProvider->add<BallSpawnerSystem>();
        assert( nullptr != ballSpawnerSystem );

        sysProvider->registerClass<StaticStuffSystem>();
        auto staticStuffSystem = sysProvider->add<StaticStuffSystem>();
        assert( nullptr != staticStuffSystem );

        //Spawn
        Floor0 = spawnFloor( gEngineApplication->getTextureManager(), { 15.0f, -15.0f }, GeometryHelpers::degreesToRadians( 45.0f ) );
        Floor1 = spawnFloor( gEngineApplication->getTextureManager(), { -15.0f, -15.0f }, GeometryHelpers::degreesToRadians( -45.0f ) );

        Floor2 = spawnFloor( gEngineApplication->getTextureManager(), { 15.0f, 15.0f }, GeometryHelpers::degreesToRadians( -45.0f ) );
        Floor3 = spawnFloor( gEngineApplication->getTextureManager(), { -15.0f, 15.0f }, GeometryHelpers::degreesToRadians( 45.0f ) );

        FloorList.push_back( Floor0 );
        FloorList.push_back( Floor1 );
        FloorList.push_back( Floor2 );
        FloorList.push_back( Floor3 );

        //Floor controller
        FloorController = gEntities->requestEntity();

        puma::IInputComponent* ic = gComponents->add<IInputComponent>( FloorController ).get();
        ic->addInputMap( TestInputActions::ToggleFloorEntity, { puma::nina::KeyboardKey::KB_I, puma::InputModifier_IGNORE, puma::nina::InputButtonEvent::Pressed } );
        ic->addInputMap( TestInputActions::ToggleFloorPhysics, { puma::nina::KeyboardKey::KB_K, puma::InputModifier_IGNORE, puma::nina::InputButtonEvent::Pressed } );

        gSystems->get<IInputSystem>()->registerEntity( FloorController );

        //[fpuma] TODO Loading all assets now to prevent a race condition later.
        // I need to create a ResourceManager that supports multithreading
        auto textureManager = gEngineApplication->getTextureManager();
        textureManager->loadTexture( "../assets/green.png" );
        textureManager->loadTexture( "../assets/bricks.jpg" );
        textureManager->loadTexture( "../assets/tennisball.png" );

    }

    void Test::update( float _deltaTime )
    {
        puma::pina::ComponentProvider* cp = gComponents;
        puma::pina::EntityProvider* ep = gEntities;
        
        puma::IInputComponent* inputComp = cp->get<IInputComponent>( FloorController );
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
            puma::ICollisionComponent* colComp = cp->get<ICollisionComponent>( Floor2 );

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

        sysProvider->get<IInputSystem>()->unregisterEntity( FloorController );
        gComponents->remove<IInputComponent>( FloorController );
        gEntities->disposeEntity( FloorController );

        sysProvider->remove<BallSpawnerSystem>();
        sysProvider->remove<StaticStuffSystem>();

        sysProvider->remove<IInputSystem>();
        sysProvider->remove<IRenderSystem>();
        sysProvider->remove<ICollisionSystem>();
    }

    void initPhysics()
    {
        auto collisitonSystemPtr = gSystems->get<puma::ICollisionSystem>();
        collisitonSystemPtr->setGravity( { 0.0f, -10.0f } );
        collisitonSystemPtr->setCollisionCompatibility( kCollisionCompatibility );
    }
}
