#include "precompiledengine.h"

#include "ballspawner.h"

#include <data/collisionindexes.h>

#include <engine/services/ecsservice.h>
#include <engine/services/systemsservice.h>

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
    puma::pina::Entity spawnBackground( puma::nina::ITextureManager* _textureManager, const puma::Position& _pos )
    {
        puma::pina::Entity result = gEntities->requestEntity();
        puma::pina::ComponentProvider* componentProvider = gComponents;

        auto locationComponent = componentProvider->add<puma::ILocationComponent>( result );
        auto renderComponent = componentProvider->add<puma::IRenderComponent>( result );
        auto inputComponent = componentProvider->add<puma::IInputComponent>( result );

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

        //Input
        inputComponent->addInputMap( TestInputActions::MouseMove, { puma::InputModifier_IGNORE } );

        gSystems->get<puma::IInputSystem>()->registerEntity( result );

        return result;
    }

    void unspawnBackground( puma::pina::Entity _ballEntity )
    {
        gSystems->get<puma::IRenderSystem>()->unregisterEntity( _ballEntity );
        gSystems->get<puma::IInputSystem>()->unregisterEntity( _ballEntity );

        puma::pina::ComponentProvider* componentProvider = gComponents;

        componentProvider->remove<puma::ILocationComponent>( _ballEntity );
        componentProvider->remove<puma::IRenderComponent>( _ballEntity );
        componentProvider->remove<puma::IInputComponent>( _ballEntity );

        gEntities->disposeEntity( _ballEntity );
    }
}