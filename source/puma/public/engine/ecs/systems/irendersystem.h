#pragma once

#include <engine/ecs/base/entity.h>
#include <engine/ecs/base/isystem.h>

#include <utils/graphics/dimensions.h>

namespace puma
{
    namespace app
    {
        class IRenderer;
    }

    class IRenderSystem : public ISystem
    {
    public:

        virtual ~IRenderSystem() {}

        virtual void init() = 0;

        virtual void registerEntity( Entity _entity ) = 0;
        virtual void unregisterEntity( Entity _entity ) = 0;
    };
}