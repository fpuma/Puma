#include <precompiledengine.h>

#include "floorspawner.h"
#include <modules/leo/leodefinitions.h>

#include <engine/ecs/components/icollisioncomponent.h>
#include <engine/ecs/components/ilocationcomponent.h>
#include <engine/ecs/components/irendercomponent.h>
#include <engine/services/ecsservice.h>

#include <engine/ecs/systems/icollisionsystem.h>
#include <engine/ecs/systems/irendersystem.h>


#include <data/collisionindexes.h>


namespace test
{
    puma::Entity spawnFloor( puma::nina::ITextureManager* _textureManager, const puma::Position& _pos, float _angle )
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