#include <precompiledengine.h>

#include "test.h"


#include <data/collisionindexes.h>

#include <engine/ecs/base/entity.h>
#include <engine/ecs/base/providers/icomponentprovider.h>
#include <engine/ecs/base/providers/ientityprovider.h>
#include <engine/ecs/components/icameracomponent.h>
#include <engine/ecs/components/icollisioncomponent.h>
#include <engine/ecs/components/ilocationcomponent.h>
#include <engine/ecs/components/irendercomponent.h>
#include <engine/ecs/components/iinputcomponent.h>
#include <engine/ecs/systems/icollisionsystem.h>
#include <engine/ecs/systems/irendersystem.h>
#include <engine/ecs/systems/iinputsystem.h>
#include <engine/external/leodefinitions.h>
#include <engine/external/ninadefinitions.h>

#include <engine/services/iengineapplicationservice.h>
#include <engine/services/iloggerservice.h>
#include <engine/services/iprovidersservice.h>
#include <engine/services/isystemsservice.h>

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
            puma::IEntityProvider* entityProvider = gProviders->get<puma::IEntityProvider>();
            puma::IComponentProvider* componentProvider = gProviders->get<puma::IComponentProvider>();

            puma::Entity result = entityProvider->requestEntity();
            puma::ILocationComponent* locationComponent = componentProvider->add<puma::ILocationComponent>( result );
            puma::ICameraComponent* cameraComponent = componentProvider->add<puma::ICameraComponent>( result );

            locationComponent->setPosition( { 0.0f, 0.0f } );
            cameraComponent->setMetersPerPixel( 0.2f );

            return result;
        }

        void destroyDefaultCamera( puma::Entity _entity )
        {
            puma::IEntityProvider* entityProvider = gProviders->get<puma::IEntityProvider>();
            puma::IComponentProvider* componentProvider = gProviders->get<puma::IComponentProvider>();

            componentProvider->remove<puma::ICameraComponent>( _entity );
            componentProvider->remove<puma::ILocationComponent>( _entity );

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
        gProviders->get<IComponentProvider>()->registerClass<MoveDirectionComponent>();

        //Register systems
        gSystems->registerClass<BallSpawnerSystem>();
        BallSpawnerSystem* ballSpawnerSystem = gSystems->add<BallSpawnerSystem>();
        assert( nullptr != ballSpawnerSystem );

        gSystems->registerClass<StaticStuffSystem>();
        StaticStuffSystem* staticStuffSystem = gSystems->add<StaticStuffSystem>();
        assert( nullptr != staticStuffSystem );

        //Init systems
        ballSpawnerSystem->init();
        staticStuffSystem->init();
        gSystems->updateSystemsProperties();

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
    }

    void initPhysics()
    {
        auto collisitonSystemPtr = gSystems->get<puma::ICollisionSystem>();
        collisitonSystemPtr->init( { 0.0f, -10.0f } );
        collisitonSystemPtr->setCollisionCompatibility( kCollisionCompatibility );
    }

    puma::Entity spawnFloor( nina::ITextureManager* _textureManager, const puma::Position& _pos, float _angle )
    {
        puma::Entity result = gProviders->get<puma::IEntityProvider>()->requestEntity();
        puma::IComponentProvider* componentProvider = gProviders->get<puma::IComponentProvider>();

        puma::ILocationComponent* locationComponent = componentProvider->add<puma::ILocationComponent>( result );
        puma::IRenderComponent* renderComponent = componentProvider->add<puma::IRenderComponent>( result );
        puma::ICollisionComponent* collisionComponent = componentProvider->add<puma::ICollisionComponent>( result );

        locationComponent->setPosition( _pos );

        //Render
        puma::nina::Texture greenTexture = _textureManager->loadTexture( "../assets/green.png" );
        puma::TextureInfo textureInfo;
        textureInfo.texture = greenTexture;
        textureInfo.renderSize = { 40.0f, 8.0f };

        renderComponent->addTextureInfo( textureInfo );

        gSystems->get<puma::IRenderSystem>()->registerEntity( result );

        //Physics
        puma::leo::FrameInfo frameInfo;
        frameInfo.position = { _pos.x, _pos.y };
        frameInfo.angle = _angle;

        gSystems->get<puma::ICollisionSystem>()->registerEntity( result, frameInfo, puma::leo::FrameType::Static );

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
        gSystems->get<puma::IRenderSystem>()->unregisterEntity( _floorEntity );
        gSystems->get<puma::ICollisionSystem>()->unregisterEntity( _floorEntity );

        puma::IComponentProvider* componentProvider = gProviders->get<puma::IComponentProvider>();

        componentProvider->remove<puma::ILocationComponent>( _floorEntity );
        componentProvider->remove<puma::IRenderComponent>( _floorEntity );
        componentProvider->remove<puma::ICollisionComponent>( _floorEntity );

        gProviders->get<puma::IEntityProvider>()->disposeEntity( _floorEntity );

    }
}
