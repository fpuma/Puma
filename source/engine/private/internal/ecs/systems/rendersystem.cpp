#include <precompiledengine.h>

#include "rendersystem.h"

#include <application/irenderer.h>
#include <application/iwindow.h>

#include <engine/ecs/base/entity.h>

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

    void RenderSystem::queueRenderables( QueueRenderableCallback _queueRenderableCallback )
    {
        ComponentProvider* componentProvider = gProviders->get<ComponentProvider>();

        for ( const Entity& entity : m_nonPhysicalEntities )
        {
            RenderComponent* renderComponent = componentProvider->get<RenderComponent>( entity );
            LocationComponent* locationComponent = componentProvider->get<LocationComponent>( entity );

            for ( const TextureInfo& textureInfo : renderComponent->getTextureInfoContainer() )
            {
                _queueRenderableCallback( textureInfo.texture,
                    textureInfo.textureSample,
                    textureInfo.renderSize,
                    locationComponent->getPosition() + textureInfo.offset,
                    locationComponent->getDegreesRotation() );
            }
        }

        for ( const Entity& entity : m_physicalEntities )
        {
            RenderComponent* renderComponent = componentProvider->get<RenderComponent>( entity );
            LocationComponent* locationComponent = componentProvider->get<LocationComponent>( entity );

            for ( const TextureInfo& textureInfo : renderComponent->getTextureInfoContainer() )
            {
                _queueRenderableCallback( textureInfo.texture,
                    textureInfo.textureSample,
                    textureInfo.renderSize,
                    locationComponent->getPosition() + textureInfo.offset,
                    locationComponent->getDegreesRotation() );
            }
        }
    }

    void RenderSystem::registerEntity( Entity _entity )
    {
        assert( entityComponentCheck( _entity ) );
        assert( m_nonPhysicalEntities.find( _entity ) == m_nonPhysicalEntities.end() ); //This entity has already been registered
        assert( m_physicalEntities.find( _entity ) == m_physicalEntities.end() ); //This entity has already been registered

        ComponentProvider* componentProvider = gProviders->get<ComponentProvider>();

        if ( componentProvider->exists<CollisionComponent>( _entity ) )
        {
            m_physicalEntities.emplace( _entity );
        }
        else
        {
            m_nonPhysicalEntities.emplace( _entity );
        }
    }

    void RenderSystem::unregisterEntity( Entity _entity )
    {
        if ( m_nonPhysicalEntities.find( _entity ) != m_nonPhysicalEntities.end() )
        {
            m_nonPhysicalEntities.erase( _entity );
        }
        else
        {
            assert( m_physicalEntities.find( _entity ) != m_physicalEntities.end() ); //This entity is not registered to this system
            m_physicalEntities.erase( _entity );
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