#pragma once

#include <engine/resources/renderable.h>

namespace puma
{
    using Renderables = std::vector<Renderable>;
    using RenderablesBackInserter = std::back_insert_iterator<Renderables>;
}