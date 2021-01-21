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
#include <internal/services/applicationservice.h>

#include <physics/geometry/overlapcheck.h>
#include <utils/geometry/shapes/shape.h>

namespace puma
{
    namespace
    {

        Rectangle getCameraFrustum( ComponentProvider* _componentProvider, Entity _cameraEntity, app::WindowHandle _windowHandle )
        {
            const LocationComponent* locationComponent = _componentProvider->get<LocationComponent>( _cameraEntity );
            const CameraComponent* cameraComponent = _componentProvider->get<CameraComponent>( _cameraEntity );

            assert( (nullptr != locationComponent) && (nullptr != cameraComponent) );

            Extent windowExtent = gApplication->getWindow( _windowHandle )->getExtent();

            Rectangle result;

            Position cameraPos = locationComponent->getPosition();
            float screenMetersWidth = (float)windowExtent.width * cameraComponent->getMetersPerPixel();
            float screenMetersHeight = (float)windowExtent.height * cameraComponent->getMetersPerPixel();

            float upperX = cameraPos.x + (screenMetersWidth / 2.0f);
            float lowerX = cameraPos.x - (screenMetersWidth / 2.0f);
            float upperY = cameraPos.y + (screenMetersHeight / 2.0f);
            float lowerY = cameraPos.y - (screenMetersHeight / 2.0f);

            result.upperBoundary = { upperX, upperY };
            result.lowerBoundary = { lowerX, lowerY };

            return result;
        }

        Entity buildDefaultCamera()
        {
            EntityProvider* entityProvider = gProviders->get<EntityProvider>();
            ComponentProvider* componentProvider = gProviders->get<ComponentProvider>();

            Entity result = entityProvider->requestEntity();
            componentProvider->add<LocationComponent>( result );
            CameraComponent* cameraComponent = componentProvider->add<CameraComponent>( result );

            cameraComponent->setMetersPerPixel( 1.0f );

            return result;
        }

        void destroyDefaultCamera( Entity _entity )
        {
            EntityProvider* entityProvider = gProviders->get<EntityProvider>();
            ComponentProvider* componentProvider = gProviders->get<ComponentProvider>();

            componentProvider->remove<CameraComponent>( _entity );
            componentProvider->remove<LocationComponent>( _entity );

            entityProvider->disposeEntity( _entity );
        }

        Rectangle getAABB( const LocationComponent* _locationComponent, const RenderComponent* _renderComponent )
        {
            assert( (nullptr != _locationComponent) && (nullptr != _renderComponent) );

            Position position = _locationComponent->getPosition();
            RenderSize renderSize = _renderComponent->getSize();

            float upperX = position.x + (renderSize.x / 2.0f);
            float lowerX = position.x - (renderSize.x / 2.0f);
            float upperY = position.y + (renderSize.y / 2.0f);
            float lowerY = position.y - (renderSize.y / 2.0f);

            Rectangle result;
            result.upperBoundary = { upperX, upperY };
            result.lowerBoundary = { lowerX, lowerY };

            return result;
        }
    }

    void RenderSystem::init( Extent _windowExtent, const char* _windowName )
    {
        m_windowHandle = gApplication->createWindow( _windowExtent, _windowName );
        m_properties.updateBitMask = (SystemUpdateBitMask)SystemUpdateFlag::PostPhysicsUpdate | (SystemUpdateBitMask)SystemUpdateFlag::PrePhysicsUpdate;
        m_cameraEntity = buildDefaultCamera();
    }

    void RenderSystem::uninit()
    {
        destroyDefaultCamera( m_cameraEntity );
        gApplication->removeWindow( m_windowHandle );
    }

    app::IRenderer* RenderSystem::getRenderer()
    {
        return gApplication->getWindow( m_windowHandle )->getRenderer();
    }

    const app::IRenderer* RenderSystem::getRenderer() const
    {
        return gApplication->getWindow( m_windowHandle )->getRenderer();
    }

    void RenderSystem::prePhysicsUpdate( float _deltaTime )
    {
        m_texturesToRenderCount = 0;
        updateTexturesToRender( m_nonPhysicalEntities );
    }

    void RenderSystem::postPhysicsUpdate( float _deltaTime )
    {
        updateTexturesToRender( m_physicalEntities );
    }

    void RenderSystem::render() const
    {
        app::IRenderer* renderer = gApplication->getWindow(m_windowHandle)->getRenderer();

        for ( u32 index = 0; index < m_texturesToRenderCount; ++index )
        {
            renderer->renderTexture( m_texturesToRender[index].texture,
                m_texturesToRender[index].uvExtent,
                m_texturesToRender[index].screenExtent,
                m_texturesToRender[index].rotationDegrees );
        }

    }

    void RenderSystem::setCameraEntity( Entity _cameraEntity )
    {
#ifdef _DEBUG
        ComponentProvider* componentProvider = gProviders->get<ComponentProvider>();
        CameraComponent* cameraComponent = componentProvider->get<CameraComponent>( _cameraEntity );
        LocationComponent* locationComponent = componentProvider->get<LocationComponent>( _cameraEntity );
        assert( (nullptr != cameraComponent) && (nullptr != locationComponent) );
#endif
        m_cameraEntity = _cameraEntity;
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

    void RenderSystem::updateTexturesToRender( const std::set<Entity>& _entitesToRender )
    {
        ComponentProvider* componentProvider = gProviders->get<ComponentProvider>();

        Rectangle frustum = getCameraFrustum( componentProvider, m_cameraEntity, m_windowHandle );

        float metersPerPixel = componentProvider->get<CameraComponent>( m_cameraEntity )->getMetersPerPixel();

        for ( const Entity& entity : _entitesToRender )
        {
            if ( !gProviders->get<EntityProvider>()->isEntityEnabled( entity ) ) continue;

            const RenderComponent* renderComponent = componentProvider->get<RenderComponent>( entity );

            if ( !renderComponent->isEnabled() ) continue;

            const LocationComponent* locationComponent = componentProvider->get<LocationComponent>( entity );

            Rectangle entityAABB = getAABB( locationComponent, renderComponent );

            if ( physics::areShapesOverLapping( entityAABB, frustum ) )
            {
                assert( m_texturesToRenderCount < kConcurrentTexturePool ); //The concurrent texture pool is not big enough, consider increasing  kConcurrentTexturePool

                m_texturesToRender[m_texturesToRenderCount].texture = renderComponent->getTexture();
                m_texturesToRender[m_texturesToRenderCount].uvExtent = renderComponent->getSampledExtent();
                m_texturesToRender[m_texturesToRenderCount].screenExtent.xPos = (s32)((entityAABB.lowerBoundary.x - frustum.lowerBoundary.x) / metersPerPixel);
                m_texturesToRender[m_texturesToRenderCount].screenExtent.yPos = (s32)((frustum.upperBoundary.y - entityAABB.upperBoundary.y) / metersPerPixel);
                m_texturesToRender[m_texturesToRenderCount].screenExtent.width = (s32)(renderComponent->getSize().x / metersPerPixel);
                m_texturesToRender[m_texturesToRenderCount].screenExtent.height = (s32)(renderComponent->getSize().y / metersPerPixel);
                m_texturesToRender[m_texturesToRenderCount].rotationDegrees = locationComponent->getDegreesRotation();

                ++m_texturesToRenderCount;
            }
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