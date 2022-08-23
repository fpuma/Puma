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

namespace test
{

    namespace
    {
        puma::Entity MyDefaultCamera;
        puma::Entity Floor0;
        puma::Entity Floor1;
        puma::Entity Floor2;
        puma::Entity Floor3;

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

    puma::Entity spawnFloor( nina::ITextureManager* _textureManager, const puma::Position& _pos, float _angle );
    void unspawnFloor( puma::Entity _floorEntity );

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

        //Register components
        gComponents->registerComponent<MoveDirectionComponent>();

        //Register systems
        gSystems->registerSystem<BallSpawnerSystem>();
        auto ballSpawnerSystem = gSystems->addSystem<BallSpawnerSystem>();
        assert( nullptr != ballSpawnerSystem );

        gSystems->registerSystem<StaticStuffSystem>();
        auto staticStuffSystem = gSystems->addSystem<StaticStuffSystem>();
        assert( nullptr != staticStuffSystem );

        //Init systems
        ballSpawnerSystem->init();
        staticStuffSystem->init();

        //Spawn
        Floor0 = spawnFloor( gEngineApplication->getTextureManager(), { 15.0f, -15.0f, 0.0f }, 45.0f );
        Floor1 = spawnFloor( gEngineApplication->getTextureManager(), { -15.0f, -15.0f, 0.0f }, -45.0f );

        Floor2 = spawnFloor( gEngineApplication->getTextureManager(), { 15.0f, 15.0f, 0.0f }, -45.0f );
        Floor3 = spawnFloor( gEngineApplication->getTextureManager(), { -15.0f, 15.0f, 0.0f }, 45.0f );

        //[fpuma] TODO Loading all assets now to prevent a race condition later.
        // I need to create a ResourceManager that supports multithreading
        auto textureManager = gEngineApplication->getTextureManager();
        textureManager->loadTexture( "../assets/green.png" );
        textureManager->loadTexture( "../assets/bricks.jpg" );
        textureManager->loadTexture( "../assets/tennisball.png" );
    }

    void Test::update( float _deltaTime )
    {

    }

    void Test::uninit()
    {
        destroyDefaultCamera( MyDefaultCamera );

        unspawnFloor( Floor0 );
        unspawnFloor( Floor1 );
        unspawnFloor( Floor2 );
        unspawnFloor( Floor3 );

        gSystems->getSystem<StaticStuffSystem>()->uninit();
        gSystems->getSystem <BallSpawnerSystem>()->uninit();
    }

    void initPhysics()
    {
        auto collisitonSystemPtr = gSystems->getSystem<puma::ICollisionSystem>();
        collisitonSystemPtr->init( { 0.0f, -10.0f } );
        collisitonSystemPtr->setCollisionCompatibility( kCollisionCompatibility );
    }

    puma::Entity spawnFloor( nina::ITextureManager* _textureManager, const puma::Position& _pos, float _angle )
    {
        puma::Entity result = gEntities->requestEntity();
        puma::ComponentProvider* componentProvider = gComponents;

        auto locationComponent = componentProvider->addComponent<puma::ILocationComponent>( result );
        auto renderComponent = componentProvider->addComponent<puma::IRenderComponent>( result );
        auto collisionComponent = componentProvider->addComponent<puma::ICollisionComponent>( result );

        locationComponent->setPosition( _pos );

        //Render
        puma::nina::Texture greenTexture = _textureManager->loadTexture( "../assets/green.png" );
        puma::TextureInfo textureInfo;
        textureInfo.texture = greenTexture;
        textureInfo.renderSize = { 40.0f, 8.0f };

        renderComponent->addTextureInfo( textureInfo );

        gSystems->getSystem<puma::IRenderSystem>()->registerEntity( result );

        //Physics
        puma::leo::FrameInfo frameInfo;
        frameInfo.position = { _pos.x, _pos.y };
        frameInfo.angle = _angle;

        gSystems->getSystem<puma::ICollisionSystem>()->registerEntity( result, frameInfo, puma::leo::FrameType::Static );

        puma::Rectangle floorShape;
        floorShape.lowerBoundary = { -20.0f, -4.0f };
        floorShape.upperBoundary = { 20.0f, 4.0f };
        puma::leo::BodyInfo floorBodyInfo;
        floorBodyInfo.collisionIndex = TestCollisionIndexes::Floor;
        floorBodyInfo.shape.setAsPolygon( floorShape );
        floorBodyInfo.restitution = 0.0f;

        collisionComponent->addBody( floorBodyInfo );

        return result;
    }

    void unspawnFloor( puma::Entity _floorEntity )
    {
        gSystems->getSystem<puma::IRenderSystem>()->unregisterEntity( _floorEntity );
        gSystems->getSystem<puma::ICollisionSystem>()->unregisterEntity( _floorEntity );

        puma::ComponentProvider* componentProvider = gComponents;

        componentProvider->removeComponent<puma::ILocationComponent>( _floorEntity );
        componentProvider->removeComponent<puma::IRenderComponent>( _floorEntity );
        componentProvider->removeComponent<puma::ICollisionComponent>( _floorEntity );

        gEntities->disposeEntity( _floorEntity );

    }
}
