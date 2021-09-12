#include <precompiledengine.h>

#include "rendersystem.h"

#include <application/irenderer.h>
#include <application/iwindow.h>

#include <engine/ecs/base/entity.h>
#include <engine/renderer/irenderqueue.h>

#include <internal/ecs/base/providers/componentprovider.h>
#include <internal/ecs/base/providers/entityprovider.h>

#include <internal/ecs/components/cameracomponent.h>
#include <internal/ecs/components/collisioncomponent.h>
#include <internal/ecs/components/locationcomponent.h>
#include <internal/ecs/components/rendercomponent.h>

#include <internal/services/providersservice.h>

#include <physics/geometry/overlapcheck.h>
#include <utils/geometry/shapes/shape.h>

namespace puma
{

    RenderSystem::RenderSystem()
    {
        init();
    }

    void RenderSystem::init()
    {
        m_properties.updateBitMask = (SystemUpdateBitMask)SystemUpdateFlag::QueueRenderables;
    }

    void RenderSystem::uninit()
    {
    }

    void RenderSystem::queueRenderables( IRenderQueue& _renderQueue )
    {
        ComponentProvider* componentProvider = gProviders->get<ComponentProvider>();

        for ( const Entity& entity : m_entities )
        {
            RenderComponent* renderComponent = componentProvider->get<RenderComponent>( entity );
            LocationComponent* locationComponent = componentProvider->get<LocationComponent>( entity );

            for ( const TextureInfo& textureInfo : renderComponent->getTextureInfoContainer() )
            {
                _renderQueue.addRenderableTexture( textureInfo.texture,
                    textureInfo.textureSample,
                    textureInfo.renderSize,
                    locationComponent->getPosition() + textureInfo.offset,
                    locationComponent->getDegreesRotation() );
                
#ifdef _DEBUG
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
        ComponentProvider* componentProvider = gProviders->get<ComponentProvider>();
        bool hasRenderComponent = componentProvider->exists<RenderComponent>( _entity );
        bool hasLocationComponent = componentProvider->exists<LocationComponent>( _entity );
        return (hasRenderComponent && hasLocationComponent);
    }
#endif
}