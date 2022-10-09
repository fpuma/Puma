#pragma once

#include <utils/graphics/dimensions.h>
#include <engine/utils/position.h>
#include <engine/utils/renderdefinitions.h>

namespace puma::erh
{
    bool shouldRender( const ShapeVerticesList& _vertices, const Rectangle& _frustum );

    bool shouldRender( const Rectangle& _aabb, const Rectangle& _frustum );
}