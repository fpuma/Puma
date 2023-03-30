#include <precompiledengine.h>

#include "floorspawner.h"
#include <modules/leo/leodefinitions.h>

#include <engine/ecs/components/icollisioncomponent.h>
#include <engine/ecs/components/ilocationcomponent.h>
#include <engine/ecs/components/irendercomponent.h>
#include <engine/services/ecsservice.h>
#include <engine/services/systemsservice.h>

#include <engine/ecs/systems/icollisionsystem.h>
#include <engine/ecs/systems/irendersystem.h>


#include <data/collisionindexes.h>


namespace test
{
    puma::pina::Entity spawnFloor( puma::nina::ITextureManager* _textureManager, const puma::Position& _pos, float _angle )
    {
        puma::pina::Entity result = gEntities->requestEntity();
        puma::pina::ComponentProvider* componentProvider = gComponents;

        auto locationComponent = componentProvider->add<puma::ILocationComponent>( result );
        auto renderComponent = componentProvider->add<puma::IRenderComponent>( result );
        auto collisionComponent = componentProvider->add<puma::ICollisionComponent>( result );

        locationComponent->setPosition( _pos );

        //Render
        puma::nina::Texture greenTexture = _textureManager->loadTexture( "../assets/green.png" );
        puma::TextureInfo textureInfo;
        textureInfo.texture = greenTexture;
        textureInfo.renderSize = { 40.0f, 8.0f };

        renderComponent->addTextureInfo( textureInfo );

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

    void unspawnFloor( puma::pina::Entity _floorEntity )
    {
        gSystems->getSystem<puma::ICollisionSystem>()->unregisterEntity( _floorEntity );

        puma::pina::ComponentProvider* componentProvider = gComponents;

        componentProvider->remove<puma::ILocationComponent>( _floorEntity );
        componentProvider->remove<puma::IRenderComponent>( _floorEntity );
        componentProvider->remove<puma::ICollisionComponent>( _floorEntity );

        gEntities->disposeEntity( _floorEntity );

    }
}