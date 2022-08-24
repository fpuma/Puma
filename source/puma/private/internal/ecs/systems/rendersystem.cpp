#include <precompiledengine.h>

#include "rendersystem.h"

#include <nina/application/irenderer.h>
#include <nina/application/iwindow.h>

#include <modules/pina/entity.h>
#include <engine/renderer/irenderqueue.h>
#include <engine/services/ecsservice.h>

#include <internal/ecs/components/cameracomponent.h>
#include <internal/ecs/components/collisioncomponent.h>
#include <internal/ecs/components/locationcomponent.h>
#include <internal/ecs/components/rendercomponent.h>

#include <utils/geometry/shapes/shape.h>

//#define RENDER_SYSTEM_DEBUG

namespace puma
{

    RenderSystem::RenderSystem()
    {}

    void RenderSystem::queueRenderables( IRenderQueue& _renderQueue )
    {
        ComponentProvider* componentProvider = gComponents;

        for ( const Entity& entity : m_entities )
        {
            if (!gEntities->isEntityEnabled( entity )) continue;

            RenderComponent* renderComponent = componentProvider->getComponent<RenderComponent>( entity );

            if (!renderComponent->isEnabled()) continue;

            LocationComponent* locationComponent = componentProvider->getComponent<LocationComponent>( entity );

            for ( const TextureInfo& textureInfo : renderComponent->getTextureInfoContainer() )
            {

                Position offsetPosition = locationComponent->getPosition() + textureInfo.offset;

                _renderQueue.addRenderableTexture( textureInfo.texture,
                    textureInfo.textureSample,
                    textureInfo.renderSize,
                    offsetPosition,
                    locationComponent->getDegreesRotation(),
                    textureInfo.renderLayer );
                
#ifdef RENDER_SYSTEM_DEBUG
                std::string posString = formatString( "x: %.3f | y: %.3f", locationComponent->getPosition().x, locationComponent->getPosition().y );
                _renderQueue.addRenderableText( posString, Color::Red(), locationComponent->getPosition() );
#endif
            }
        }
    }

    void RenderSystem::registerEntity( Entity _entity )
    {
        assert( entityComponentCheck( _entity ) );
        assert( m_entities.find( _entity ) == m_entities.end() ); //This entity has already been registered

        m_entities.emplace( _entity );
    }

    void RenderSystem::unregisterEntity( Entity _entity )
    {
        if ( m_entities.find( _entity ) != m_entities.end() )
        {
            m_entities.erase( _entity );
        }
    }

#ifdef _DEBUG
    bool RenderSystem::entityComponentCheck( Entity _entity )
    {
        ComponentProvider* componentProvider = gComponents;
        bool hasRenderComponent = componentProvider->containsComponent<RenderComponent>( _entity );
        bool hasLocationComponent = componentProvider->containsComponent<LocationComponent>( _entity );
        return (hasRenderComponent && hasLocationComponent);
    }
#endif
}