#include <precompiledengine.h>

#include "enginerenderer.h"

#include <application/irenderer.h>

#include <engine/services/iprovidersservice.h>

#include <internal/ecs/base/providers/componentprovider.h>
#include <internal/ecs/components/cameracomponent.h>
#include <internal/ecs/components/locationcomponent.h>
#include <internal/services/systemsservice.h>
#include <internal/services/engineapplicationservice.h>


namespace puma
{
    namespace
    {
        void getCameraInfo(Rectangle& _outFrustum, float& _outMetersPerPixel)
        {
            Entity cameraEntity = gInternalEngineApplication->getCameraEntity();
            ComponentProvider* componentProvider = gProviders->get<ComponentProvider>();

            const LocationComponent* locationComponent = componentProvider->get<LocationComponent>( cameraEntity );
            const CameraComponent* cameraComponent = componentProvider->get<CameraComponent>( cameraEntity );

            assert( (nullptr != locationComponent) && (nullptr != cameraComponent) );

            Extent windowExtent = gInternalEngineApplication->getWindow()->getExtent();

            _outMetersPerPixel = cameraComponent->getMetersPerPixel();

            Position cameraPos = locationComponent->getPosition();
            float screenMetersWidth = (float)windowExtent.width * _outMetersPerPixel;
            float screenMetersHeight = (float)windowExtent.height * _outMetersPerPixel;

            float upperX = cameraPos.x + (screenMetersWidth / 2.0f);
            float lowerX = cameraPos.x - (screenMetersWidth / 2.0f);
            float upperY = cameraPos.y + (screenMetersHeight / 2.0f);
            float lowerY = cameraPos.y - (screenMetersHeight / 2.0f);

            _outFrustum.upperBoundary = { upperX, upperY };
            _outFrustum.lowerBoundary = { lowerX, lowerY };
        }

        Rectangle getAABB( Position _position, RenderSize _renderSize )
        {
            float upperX = _position.x + (_renderSize.x / 2.0f);
            float lowerX = _position.x - (_renderSize.x / 2.0f);
            float upperY = _position.y + (_renderSize.y / 2.0f);
            float lowerY = _position.y - (_renderSize.y / 2.0f);

            Rectangle result;
            result.upperBoundary = { upperX, upperY };
            result.lowerBoundary = { lowerX, lowerY };

            return result;
        }
    }

    void EngineRenderer::beginRender()
    {
        gInternalEngineApplication->getRenderer()->beginRender();
    }

    void EngineRenderer::endRender()
    {
        gInternalEngineApplication->getRenderer()->endRender();
    }

    void EngineRenderer::render()
    {
        m_renderables.clear();
        queueRenderables();

        for ( const Renderable& renderable : m_renderables )
        {
            gInternalEngineApplication->getRenderer()->renderTexture( renderable.getTexture(),
                renderable.getSampledExtent(),
                renderable.getScreenExtent(),
                renderable.getRotationDegrees() );
        }

    }

    void EngineRenderer::queueRenderables()
    {
        gInternalSystems->queueRenderables( [this]( AppTexture _texture, AppTextureSample _textureSample, RenderSize _renderSize, Position _position, float _rotation )
        {
            queueRenderableCallback( _texture, _textureSample, _renderSize, _position, _rotation );
        } );
    }

    void EngineRenderer::queueRenderableCallback( AppTexture _texture, AppTextureSample _textureSample, RenderSize _renderSize, Position _position, float _rotation )
    {
        Rectangle frustum;
        float metersPerPixel;
        getCameraInfo(frustum, metersPerPixel);

        Renderable renderable;
        renderable.setTexture( _texture, _textureSample );
        renderable.setRotationDegrees( _rotation );

        Extent screenExtent;

        Rectangle boundingBox = getAABB( _position, _renderSize );

        screenExtent.xPos = (s32)((boundingBox.lowerBoundary.x - frustum.lowerBoundary.x) / metersPerPixel);
        screenExtent.yPos = (s32)((frustum.upperBoundary.y - boundingBox.upperBoundary.y) / metersPerPixel);
        screenExtent.width = (s32)(_renderSize.x / metersPerPixel);
        screenExtent.height = (s32)(_renderSize.y / metersPerPixel);

        renderable.setScreenExtent( std::move( screenExtent ) );

        m_renderables.emplace_back( renderable );
    }
}