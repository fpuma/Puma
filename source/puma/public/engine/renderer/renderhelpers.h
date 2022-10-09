#pragma once

#include <utils/graphics/dimensions.h>
#include <engine/utils/position.h>
#include <engine/utils/renderdefinitions.h>

namespace puma::erh
{
    struct CameraInfo
    {
        Position position;
        Rectangle frustum;
        float metersPerPixel;
    };

    CameraInfo getCameraInfo();

    Rectangle getAABB( Position _position, RenderSize _renderSize );

    ScreenPos worldPointToScreen( const Position& _position );
    Position screenPointToWorld( const ScreenPos& _position );
}