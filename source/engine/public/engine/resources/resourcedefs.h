#pragma once

#include <engine/application/applicationdefinitions.h>
#include <engine/resources/renderable.h>

#include <engine/utils/position.h>

namespace puma
{
    using Renderables = std::vector<Renderable>;

    using QueueRenderableCallback = std::function<void( AppTexture, AppTextureSample, RenderSize, Position, float )>;
}