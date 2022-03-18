#include "precompiledengine.h"

#include "ballspawner.h"

#include <data/collisionindexes.h>

#include <engine/ecs/base/providers/ientityprovider.h>
#include <engine/ecs/base/providers/icomponentprovider.h>

#include <engine/services/iprovidersservice.h>
#include <engine/services/isystemsservice.h>

#include <engine/ecs/components/icollisioncomponent.h>
#include <engine/ecs/components/irendercomponent.h>
#include <engine/ecs/components/ilocationcomponent.h>

#include <engine/ecs/systems/irendersystem.h>
#include <engine/ecs/systems/icollisionsystem.h>


namespace test
{
    namespace
    {
        constexpr float kBallRadius = 1.0f;
    }

    puma::Entity spawnBall( puma::app::ITextureManager* _textureManager, const puma::Position& _pos )
    {
        puma::Entity result = gProviders->get<puma::IEntityProvider>()->requestEntity();
        puma::IComponentProvider* componentProvider = gProviders->get<puma::IComponentProvider>();

        puma::ILocationComponent* locationComponent = componentProvider->add<puma::ILocationComponent>( result );
        puma::IRenderComponent* renderComponent = componentProvider->add<puma::IRenderComponent>( result );
        puma::ICollisionComponent* collisionComponent = componentProvider->add<puma::ICollisionComponent>( result );

        puma::IRenderSystem* renderSystem = gSystems->get<puma::IRenderSystem>();

        locationComponent->setPosition( _pos );

        //Render
        puma::app::Texture tennisTexture = _textureManager->loadTexture( "../assets/tennisball.png" );
        puma::TextureInfo textureInfo;
        textureInfo.texture = tennisTexture;
        textureInfo.renderSize = { kBallRadius * 2.0f, kBallRadius * 2.0f };
        textureInfo.textureSample = { 1.5f,1.5f };
        textureInfo.renderLayer = puma::RenderLayer( 5 );

        renderComponent->addTextureInfo( textureInfo );
        renderSystem->registerEntity( result );


        //Physics
        puma::LeoFrameInfo frameInfo;
        frameInfo.position = { _pos.x, _pos.y };
        gSystems->get<puma::ICollisionSystem>()->registerEntity( result, frameInfo, puma::LeoFrameType::Dynamic );

        puma::Circle ballShape;
        ballShape.radius = kBallRadius;
        puma::LeoBodyInfo ballBodyInfo;
        ballBodyInfo.density = 1.0f;
        ballBodyInfo.shape.setAsCircle( ballShape );
        ballBodyInfo.collisionIndex = TestCollisionIndexes::Ball;
        //ballBodyInfo.restitution = 0.0f;
        ballBodyInfo.restitution = 1.1f;

        collisionComponent->addBody( ballBodyInfo );

        return result;
    }

    void unspawnBall( puma::Entity _ballEntity )
    {
        gSystems->get<puma::IRenderSystem>()->unregisterEntity( _ballEntity );
        gSystems->get<puma::ICollisionSystem>()->unregisterEntity( _ballEntity );

        puma::IComponentProvider* componentProvider = gProviders->get<puma::IComponentProvider>();

        componentProvider->remove<puma::ILocationComponent>( _ballEntity );
        componentProvider->remove<puma::IRenderComponent>( _ballEntity );
        componentProvider->remove<puma::ICollisionComponent>( _ballEntity );

        gProviders->get<puma::IEntityProvider>()->disposeEntity( _ballEntity );
    }
}