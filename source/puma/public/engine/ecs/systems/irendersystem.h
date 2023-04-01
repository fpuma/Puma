#pragma once

#include <pina/entity.h>
#include <engine/ecs/systems/base/isystem.h>

namespace puma
{
    class IRenderSystem : public ISystem
    {
    public:

        virtual ~IRenderSystem() {}
    };
}