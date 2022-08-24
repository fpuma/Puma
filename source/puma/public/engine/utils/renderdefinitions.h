#pragma once

#include <modules/nina/ninadefinitions.h>
#include <engine/utils/position.h>

namespace puma
{
    DECLARE_GENERIC_ID( RenderLayer, u32, kMaxU32 )

    struct RenderSize
    {
        float x = 0.0f;
        float y = 0.0f;
    };

    struct TextureInfo
    {
        nina::Texture texture;
        nina::TextureSample textureSample;
        Position offset;
        RenderSize renderSize;
        RenderLayer renderLayer;
    };

    using RotationDegrees = float;
}