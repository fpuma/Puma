#pragma once

#include <engine/application/applicationdefinitions.h>
#include <engine/utils/position.h>

namespace puma
{
    struct RenderSize
    {
        float x = 0.0f;
        float y = 0.0f;
    };

    struct TextureInfo
    {
        AppTexture texture;
        AppTextureSample textureSample;
        Position offset;
        RenderSize renderSize;
    };

    using RotationDegrees = float;
}