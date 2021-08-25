#pragma once

#include <engine/services/iprovidersservice.h>
#include <internal/ecs/base/providers/componentprovider.h>
#include <internal/ecs/components/cameracomponent.h>
#include <internal/ecs/components/locationcomponent.h>
#include <internal/services/engineapplicationservice.h>

namespace puma::erh
{
    void getCameraInfo( Rectangle& _outFrustum, float& _outMetersPerPixel )
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