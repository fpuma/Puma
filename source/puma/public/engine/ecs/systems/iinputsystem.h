#pragma once

#include <pina/entity.h>
#include <engine/ecs/systems/base/isystem.h>

namespace puma
{
    class IInputSystem : public ISystem
    {
    public:

        virtual ~IInputSystem() {}
    };
}