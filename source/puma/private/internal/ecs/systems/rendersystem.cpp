#include <precompiledengine.h>

#include "rendersystem.h"

#include <nina/application/irenderer.h>
#include <nina/application/iwindow.h>

#include <pina/entity.h>
#include <engine/renderer/irenderqueue.h>
#include <engine/services/ecsservice.h>
#include <engine/services/systemsservice.h>

#include <internal/ecs/components/cameracomponent.h>
#include <internal/ecs/components/collisioncomponent.h>
#include <internal/ecs/components/locationcomponent.h>
#include <internal/ecs/components/rendercomponent.h>

#include <utils/geometry/shapes/shape.h>

//#define RENDER_SYSTEM_DEBUG

namespace puma
{
    void RenderSystem::onInit()
    {
        gSystems->subscribeSystemUpdate<RenderSystem>( SystemUpdateId::QueueRenderables );
    }

    void RenderSystem::onUninit()
    {
        gSystems->unsubscribeSystemUpdate<RenderSystem>( SystemUpdateId::QueueRenderables );
    }

    void RenderSystem::queueRenderables( IRenderQueue& _renderQueue )
    {
        pina::ComponentProvider* componentProvider = gComponents;

        auto entities = gECS->getEntitesByComponents<IRenderComponent, ILocationComponent>();

        for ( const pina::Entity& entity : entities )
        {
            if (!gEntities->isEntityEnabled( entity )) continue;

            RenderComponent* renderComponent = componentProvider->get<RenderComponent>( entity );

            if (!renderComponent->isEnabled()) continue;

            LocationComponent* locationComponent = componentProvider->get<LocationComponent>( entity );

            for ( const TextureInfo& textureInfo : renderComponent->getTextureInfoContainer() )
            {

                Position offsetPosition = locationComponent->getPosition() + textureInfo.offset.position;
                RotationRadians offsetRadians = locationComponent->getRadiansRotation() + textureInfo.offset.radians;

                _renderQueue.addRenderableTexture( textureInfo.texture,
                    textureInfo.textureSample,
                    textureInfo.renderSize,
                    offsetPosition,
                    offsetRadians,
                    textureInfo.renderLayer );
                
#ifdef RENDER_SYSTEM_DEBUG
                std::string posString = formatString( "x: %.3f | y: %.3f", locationComponent->getPosition().x, locationComponent->getPosition().y );
                _renderQueue.addRenderableText( posString, Color::Red(), locationComponent->getPosition() );
#endif
            }
        }
    }
}