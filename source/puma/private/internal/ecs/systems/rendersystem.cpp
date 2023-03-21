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

        assert( m_entities.empty() ); //Warning not all entities have been unregistered.
        m_entities.clear();
    }

    void RenderSystem::queueRenderables( IRenderQueue& _renderQueue )
    {
        pina::ComponentProvider* componentProvider = gComponents;

        for ( const pina::Entity& entity : m_entities )
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

    void RenderSystem::registerEntity( pina::Entity _entity )
    {
        assert( entityComponentCheck( _entity ) );
        assert( m_entities.find( _entity ) == m_entities.end() ); //This entity has already been registered

        m_entities.emplace( _entity );
    }

    void RenderSystem::unregisterEntity( pina::Entity _entity )
    {
        if ( m_entities.find( _entity ) != m_entities.end() )
        {
            m_entities.erase( _entity );
        }
    }

#ifdef _DEBUG
    bool RenderSystem::entityComponentCheck( pina::Entity _entity )
    {
        pina::ComponentProvider* componentProvider = gComponents;
        bool hasRenderComponent = componentProvider->contains<RenderComponent>( _entity );
        bool hasLocationComponent = componentProvider->contains<LocationComponent>( _entity );
        return (hasRenderComponent && hasLocationComponent);
    }
#endif
}