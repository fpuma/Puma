#pragma once

#include <modules/nina/ninadefinitions.h>
#include <engine/utils/position.h>

namespace puma
{
    class RenderLayer;
}

DECLARE_GENERIC_ID( puma::RenderLayer, puma::u32, puma::kMaxU32 )

namespace puma
{
    

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