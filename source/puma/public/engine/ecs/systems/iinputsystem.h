#pragma once

#include <pina/entity.h>
#include <engine/layers/isystem.h>

namespace puma
{
    class IInputSystem : public ISystem
    {
    public:

        virtual ~IInputSystem() {}
    };
}