#pragma once

#include <modules/nina/ninadefinitions.h>
#include <engine/utils/position.h>

namespace puma
{
    DECLARE_GENERIC_ID( RenderLayer, u32, kMaxU32 )

    using RotationRadians = float;
    
    struct RenderSize
    {
        float x = 0.0f;
        float y = 0.0f;
    };

    struct RenderOffset
    {
        Position position;
        RotationRadians radians = 0.0f;
    };

    struct TextureInfo
    {
        nina::Texture texture;
        nina::TextureSample textureSample;
        RenderOffset offset;
        RenderSize renderSize;
        RenderLayer renderLayer;
    };

}