#include "precompiledengine.h"

#include "ballspawner.h"

#include <data/collisionindexes.h>

#include <engine/services/ecsservice.h>
#include <engine/services/systemsservice.h>

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

    puma::pina::Entity spawnBall( puma::nina::ITextureManager* _textureManager, const puma::Position& _pos )
    {
        puma::pina::Entity result = gEntities->requestEntity();
        puma::pina::ComponentProvider* componentProvider = gComponents;

        auto locationComponent = componentProvider->add<puma::ILocationComponent>( result );
        auto renderComponent = componentProvider->add<puma::IRenderComponent>( result );
        auto collisionComponent = componentProvider->add<puma::ICollisionComponent>( result );

        locationComponent->setPosition( _pos );

        //Render
        puma::nina::Texture tennisTexture = _textureManager->loadTexture( "../assets/tennisball.png" );
        puma::TextureInfo textureInfo;
        textureInfo.texture = tennisTexture;
        textureInfo.renderSize = { kBallRadius * 2.0f, kBallRadius * 2.0f };
        textureInfo.textureSample = { 1.5f,1.5f };
        textureInfo.renderLayer = puma::RenderLayer( 5 );

        renderComponent->addTextureInfo( textureInfo );

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

    void unspawnBall( puma::pina::Entity _ballEntity )
    {
        gSystems->getSystem<puma::ICollisionSystem>()->unregisterEntity( _ballEntity );

        puma::pina::ComponentProvider* componentProvider = gComponents;

        componentProvider->remove<puma::ILocationComponent>( _ballEntity );
        componentProvider->remove<puma::IRenderComponent>( _ballEntity );
        componentProvider->remove<puma::ICollisionComponent>( _ballEntity );

        gEntities->disposeEntity( _ballEntity );
    }
}