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
    puma::Entity spawnBackground( puma::nina::ITextureManager* _textureManager, const puma::Position& _pos )
    {
        puma::Entity result = gProviders->get<puma::IEntityProvider>()->requestEntity();
        puma::IComponentProvider* componentProvider = gProviders->get<puma::IComponentProvider>();

        puma::ILocationComponent* locationComponent = componentProvider->add<puma::ILocationComponent>( result );
        puma::IRenderComponent* renderComponent = componentProvider->add<puma::IRenderComponent>( result );

        puma::IRenderSystem* renderSystem = gSystems->get<puma::IRenderSystem>();

        locationComponent->setPosition( _pos );

        //Render
        puma::nina::Texture bricksTexture = _textureManager->loadTexture( "../assets/bricks.jpg" );
        puma::TextureInfo textureInfo;
        textureInfo.texture = bricksTexture;
        textureInfo.renderSize = { 100.0f, 100.0f };
        textureInfo.textureSample = { 1.0f,1.0f };
        textureInfo.renderLayer = puma::RenderLayer( 0 );

        renderComponent->addTextureInfo( textureInfo );
        renderSystem->registerEntity( result );

        return result;
    }

    void unspawnBackground( puma::Entity _ballEntity )
    {
        gSystems->get<puma::IRenderSystem>()->unregisterEntity( _ballEntity );

        puma::IComponentProvider* componentProvider = gProviders->get<puma::IComponentProvider>();

        componentProvider->remove<puma::ILocationComponent>( _ballEntity );
        componentProvider->remove<puma::IRenderComponent>( _ballEntity );

        gProviders->get<puma::IEntityProvider>()->disposeEntity( _ballEntity );
    }
}