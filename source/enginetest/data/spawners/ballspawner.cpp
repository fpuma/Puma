#include "precompiledengine.h"

#include "ballspawner.h"

#include <data/collisionindexes.h>

#include <engine/services/ecsservice.h>

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

    puma::Entity spawnBall( puma::nina::ITextureManager* _textureManager, const puma::Position& _pos )
    {
        puma::Entity result = gEntities->requestEntity();
        puma::ComponentProvider* componentProvider = gComponents;

        auto locationComponent = componentProvider->addComponent<puma::ILocationComponent>( result );
        auto renderComponent = componentProvider->addComponent<puma::IRenderComponent>( result );
        auto collisionComponent = componentProvider->addComponent<puma::ICollisionComponent>( result );

        puma::IRenderSystem* renderSystem = gSystems->getSystem<puma::IRenderSystem>();

        locationComponent->setPosition( _pos );

        //Render
        puma::nina::Texture tennisTexture = _textureManager->loadTexture( "../assets/tennisball.png" );
        puma::TextureInfo textureInfo;
        textureInfo.texture = tennisTexture;
        textureInfo.renderSize = { kBallRadius * 2.0f, kBallRadius * 2.0f };
        textureInfo.textureSample = { 1.5f,1.5f };
        textureInfo.renderLayer = puma::RenderLayer( 5 );

        renderComponent->addTextureInfo( textureInfo );
        renderSystem->registerEntity( result );


        //Physics
        puma::leo::FrameInfo frameInfo;
        frameInfo.position = { _pos.x, _pos.y };
        gSystems->getSystem<puma::ICollisionSystem>()->registerEntity( result, frameInfo, puma::leo::FrameType::Dynamic );

        puma::Circle ballShape;
        ballShape.radius = kBallRadius;
        puma::leo::BodyInfo ballBodyInfo;
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
        gSystems->getSystem<puma::IRenderSystem>()->unregisterEntity( _ballEntity );
        gSystems->getSystem<puma::ICollisionSystem>()->unregisterEntity( _ballEntity );

        puma::ComponentProvider* componentProvider = gComponents;

        componentProvider->removeComponent<puma::ILocationComponent>( _ballEntity );
        componentProvider->removeComponent<puma::IRenderComponent>( _ballEntity );
        componentProvider->removeComponent<puma::ICollisionComponent>( _ballEntity );

        gEntities->disposeEntity( _ballEntity );
    }
}