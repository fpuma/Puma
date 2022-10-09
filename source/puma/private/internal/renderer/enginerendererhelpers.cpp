#include <precompiledengine.h>

#include "enginerendererhelpers.h"

#include <nina/application/iwindow.h>
#include <engine/services/ecsservice.h>
#include <engine/renderer/renderhelpers.h>
#include <internal/ecs/components/cameracomponent.h>
#include <internal/ecs/components/locationcomponent.h>
#include <internal/services/engineapplicationservice.h>
#include <utils/graphics/dimensions.h>
#include <utils/geometry/geometryhelpers.h>

#include <leo/geometry/overlapcheck.h>

namespace puma::erh
{
    CameraInfo getCameraInfo()
    {
        CameraInfo result;

        Entity cameraEntity = gInternalEngineApplication->getCameraEntity();
        ComponentProvider* componentProvider = gComponents;

        const LocationComponent* locationComponent = componentProvider->getComponent<LocationComponent>( cameraEntity );
        const CameraComponent* cameraComponent = componentProvider->getComponent<CameraComponent>( cameraEntity );

        assert( (nullptr != locationComponent) && (nullptr != cameraComponent) );

        Extent windowExtent = gInternalEngineApplication->getWindowExtent();

        result.metersPerPixel = cameraComponent->getMetersPerPixel();

        Position cameraPos = locationComponent->getPosition();
        float screenMetersWidth = (float)windowExtent.width * result.metersPerPixel;
        float screenMetersHeight = (float)windowExtent.height * result.metersPerPixel;

        float upperX = cameraPos.x + (screenMetersWidth / 2.0f);
        float lowerX = cameraPos.x - (screenMetersWidth / 2.0f);
        float upperY = cameraPos.y + (screenMetersHeight / 2.0f);
        float lowerY = cameraPos.y - (screenMetersHeight / 2.0f);

        result.frustum.upperBoundary = { upperX, upperY };
        result.frustum.lowerBoundary = { lowerX, lowerY };

        return result;
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

    ScreenPos worldPointToScreen( const Position& _position )
    {
        CameraInfo camInfo = getCameraInfo();

        ScreenPos screenPosition;
        screenPosition.xCoord = static_cast<s32>((_position.x - camInfo.frustum.lowerBoundary.x) / camInfo.metersPerPixel);
        screenPosition.yCoord = static_cast<s32>((camInfo.frustum.upperBoundary.y - _position.y) / camInfo.metersPerPixel);

        return screenPosition;
    }

    Position screenPointToWorld( const ScreenPos& _position )
    {
        CameraInfo camInfo = getCameraInfo();

        Position result;
        result.x = static_cast<float>(_position.xCoord) * camInfo.metersPerPixel;
        result.y = static_cast<float>(_position.yCoord) * camInfo.metersPerPixel;

        result.x += camInfo.frustum.lowerBoundary.x;
        result.y = camInfo.frustum.upperBoundary.y - result.y;

        return result;
    }

    bool shouldRender( const ShapeVerticesList& _vertices, const Rectangle& _frustum )
    {
        const auto itMaxPointX = std::max_element( _vertices.begin(), _vertices.end(), [&]( const Vec2& point0, const Vec2& point1 ) 
        {return point0.x < point1.x; } );

        const auto itMaxPointY = std::max_element( _vertices.begin(), _vertices.end(), [&]( const Vec2& point0, const Vec2& point1 )
        {return point0.y < point1.y; } );

        const auto itMinPointX = std::max_element( _vertices.begin(), _vertices.end(), [&]( const Vec2& point0, const Vec2& point1 )
        {return point0.x > point1.x; } );

        const auto itMinPointY = std::max_element( _vertices.begin(), _vertices.end(), [&]( const Vec2& point0, const Vec2& point1 )
        {return point0.y > point1.y; } );

        Rectangle aabb = { {itMaxPointX->x, itMaxPointY->y}, {itMinPointX->x, itMinPointY->y} };

        return leo::areShapesOverLapping( aabb, _frustum );
    }

    bool shouldRender( const Rectangle& _aabb, const Rectangle& _frustum )
    {
        return leo::areShapesOverLapping( _aabb, _frustum );
    }
}