#include <precompiledapplication.h>
#include <precompiledphysics.h>
#include <precompiledengine.h>

#include "test.h"

#include <input/devices/ikeyboard.h>
#include <input/inputids.h>
#include <texturemanager/itexturemanager.h>

#include <engine/services/iprovidersservice.h>
#include <engine/services/isystemsservice.h>
#include <engine/services/iengineapplicationservice.h>

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

#include <engine/services/iloggerservice.h>

#include <engine/physics/physicsdefinitions.h>

#include <engine/services/iengineapplicationservice.h>

#include <utils/graphics/dimensions.h>

#include <utils/formatstring.h>

#include <texturemanager/itexturemanager.h>

#include <test/systems/ballspawnersystem.h>

#include <engine/ecs/base/entity.h>

#include <data/collisionindexes.h>

namespace test
{
    namespace
    {
        puma::Entity MyDefaultCamera = puma::kInvalidEntity;
        puma::Entity Floor0 = puma::kInvalidEntity;
        puma::Entity Floor1 = puma::kInvalidEntity;
        puma::Entity Floor2 = puma::kInvalidEntity;
        puma::Entity Floor3 = puma::kInvalidEntity;

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
    void initWindow();
    void initPhysics();

    puma::Entity spawnFloor( puma::app::ITextureManager* _textureManager, const puma::Position& _pos, float _angle );
    void unspawnFloor( puma::Entity _floorEntity );

    void setCamera()
    {
        MyDefaultCamera = buildDefaultCamera();
        gEngineApplication->setCameraEntity( MyDefaultCamera );
    }

    void Test::initTest()
    {
        initWindow();
        initPhysics();
        setCamera();

        gSystems->registerClass<BallSpawnerSystem>();
        BallSpawnerSystem* ballSpawnerSystem = gSystems->add<BallSpawnerSystem>();

        assert( nullptr != ballSpawnerSystem );

        ballSpawnerSystem->init();

        gSystems->updateSystemsProperties();

        Floor0 = spawnFloor( gEngineApplication->getTextureManager(), { 15.0f, -15.0f, 0.0f }, 45.0f );
        Floor1 = spawnFloor( gEngineApplication->getTextureManager(), { -15.0f, -15.0f, 0.0f }, -45.0f );

        Floor2 = spawnFloor( gEngineApplication->getTextureManager(), { 15.0f, 15.0f, 0.0f }, -45.0f );
        Floor3 = spawnFloor( gEngineApplication->getTextureManager(), { -15.0f, 15.0f, 0.0f }, 45.0f );
    }

    void Test::updateTest()
    {

    }

    void Test::uninitTest()
    {
        destroyDefaultCamera( MyDefaultCamera );

        unspawnFloor( Floor0 );
        unspawnFloor( Floor1 );
        unspawnFloor( Floor2 );
        unspawnFloor( Floor3 );
    }

    void initWindow()
    {
        puma::Extent windowExtent = { 500,500,100,100 };
        gEngineApplication->init( windowExtent, "EngineTest" );
    }

    void initPhysics()
    {
        auto collisitonSystemPtr = gSystems->get<puma::ICollisionSystem>();
        collisitonSystemPtr->init( { 0.0f, -10.0f } );
        collisitonSystemPtr->setCollisionCompatibility( kCollisionCompatibility );
    }

    puma::Entity spawnFloor( puma::app::ITextureManager* _textureManager, const puma::Position& _pos, float _angle )
    {
        puma::Entity result = gProviders->get<puma::IEntityProvider>()->requestEntity();
        puma::IComponentProvider* componentProvider = gProviders->get<puma::IComponentProvider>();

        puma::ILocationComponent* locationComponent = componentProvider->add<puma::ILocationComponent>( result );
        puma::IRenderComponent* renderComponent = componentProvider->add<puma::IRenderComponent>( result );
        puma::ICollisionComponent* collisionComponent = componentProvider->add<puma::ICollisionComponent>( result );

        locationComponent->setPosition( _pos );

        //Render
        puma::app::Texture greenTexture = _textureManager->loadTexture( "../assets/green.png" );
        puma::TextureInfo textureInfo;
        textureInfo.texture = greenTexture;
        textureInfo.renderSize = { 40.0f, 8.0f };

        renderComponent->addTextureInfo( textureInfo );

        gSystems->get<puma::IRenderSystem>()->registerEntity( result );

        //Physics
        puma::PhysicsFrameInfo frameInfo;
        frameInfo.position = { _pos.x, _pos.y };
        frameInfo.angle = _angle;

        gSystems->get<puma::ICollisionSystem>()->registerEntity( result, frameInfo, puma::PhysicsFrameType::Static );

        puma::Rectangle floorShape;
        floorShape.lowerBoundary = { -20.0f, -4.0f };
        floorShape.upperBoundary = { 20.0f, 4.0f };
        puma::PhysicsBodyInfo floorBodyInfo;
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