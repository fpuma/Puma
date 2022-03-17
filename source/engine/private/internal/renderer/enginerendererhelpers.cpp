#include <precompiledengine.h>

#include "enginerendererhelpers.h"

#include <application/iwindow.h>
#include <engine/services/iprovidersservice.h>
#include <internal/ecs/base/providers/componentprovider.h>
#include <internal/ecs/components/cameracomponent.h>
#include <internal/ecs/components/locationcomponent.h>
#include <internal/services/engineapplicationservice.h>
#include <utils/graphics/dimensions.h>
#include <utils/geometry/geometryhelpers.h>

#include <physics/geometry/overlapcheck.h>

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

    ScreenPos worldPointToScreen( const Vec2& _position, const Rectangle& _frustum, const float& _metersPerPixel )
    {
        ScreenPos screenPosition;
        screenPosition.xCoord = (s32)((_position.x - _frustum.lowerBoundary.x) / _metersPerPixel);
        screenPosition.yCoord = (s32)((_frustum.upperBoundary.y - _position.y) / _metersPerPixel);

        return screenPosition;
    }

    ScreenPos worldPointToScreen( const Position& _position, const Rectangle& _frustum, const float& _metersPerPixel )
    {
        return worldPointToScreen( Vec2{_position.x, _position.y}, _frustum, _metersPerPixel );
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

        return physics::areShapesOverLapping( aabb, _frustum );
    }

    bool shouldRender( const Rectangle& _aabb, const Rectangle& _frustum )
    {
        return physics::areShapesOverLapping( _aabb, _frustum );
    }
}