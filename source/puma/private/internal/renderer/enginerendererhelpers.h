#pragma once

#include <utils/graphics/dimensions.h>
#include <engine/utils/position.h>
#include <engine/utils/renderdefinitions.h>

namespace puma::erh
{
    void getCameraInfo( Rectangle& _outFrustum, float& _outMetersPerPixel );

    Rectangle getAABB( Position _position, RenderSize _renderSize );

    ScreenPos worldPointToScreen( const Vec2& _position, const Rectangle& _frustum, const float& _metersPerPixel );

    ScreenPos worldPointToScreen( const Position& _position, const Rectangle& _frustum, const float& _metersPerPixel );

    bool shouldRender( const ShapeVerticesList& _vertices, const Rectangle& _frustum );

    bool shouldRender( const Rectangle& _aabb, const Rectangle& _frustum );
}