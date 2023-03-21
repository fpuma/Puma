#pragma once

#include <pina/entity.h>
#include <engine/layers/isystem.h>

namespace puma
{
    class IRenderSystem : public ISystem
    {
    public:

        virtual ~IRenderSystem() {}
    };
}