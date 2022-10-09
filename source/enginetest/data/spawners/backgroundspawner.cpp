#include "precompiledengine.h"

#include "ballspawner.h"

#include <data/collisionindexes.h>

#include <engine/services/ecsservice.h>

#include <engine/ecs/components/icollisioncomponent.h>
#include <engine/ecs/components/irendercomponent.h>
#include <engine/ecs/components/ilocationcomponent.h>
#include <engine/ecs/components/iinputcomponent.h>

#include <engine/ecs/systems/irendersystem.h>
#include <engine/ecs/systems/icollisionsystem.h>
#include <engine/ecs/systems/iinputsystem.h>

#include <data/inputactions.h>

namespace test
{
    puma::Entity spawnBackground( puma::nina::ITextureManager* _textureManager, const puma::Position& _pos )
    {
        puma::Entity result = gEntities->requestEntity();
        puma::ComponentProvider* componentProvider = gComponents;

        auto locationComponent = componentProvider->addComponent<puma::ILocationComponent>( result );
        auto renderComponent = componentProvider->addComponent<puma::IRenderComponent>( result );
        auto inputComponent = componentProvider->addComponent<puma::IInputComponent>( result );

        puma::IRenderSystem* renderSystem = gSystems->getSystem<puma::IRenderSystem>();

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

        //Input
        inputComponent->addInputMap( TestInputActions::MouseMove, { puma::InputModifier_IGNORE } );

        gSystems->getSystem<puma::IInputSystem>()->registerEntity( result );

        return result;
    }

    void unspawnBackground( puma::Entity _ballEntity )
    {
        gSystems->getSystem<puma::IRenderSystem>()->unregisterEntity( _ballEntity );
        gSystems->getSystem<puma::IInputSystem>()->unregisterEntity( _ballEntity );

        puma::ComponentProvider* componentProvider = gComponents;

        componentProvider->removeComponent<puma::ILocationComponent>( _ballEntity );
        componentProvider->removeComponent<puma::IRenderComponent>( _ballEntity );
        componentProvider->removeComponent<puma::IInputComponent>( _ballEntity );

        gEntities->disposeEntity( _ballEntity );
    }
}