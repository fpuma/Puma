#pragma once

#include <modules/pina/entity.h>
#include <modules/pina/system.h>

#include <utils/graphics/dimensions.h>

namespace puma
{
    namespace app
    {
        class IRenderer;
    }

    class IRenderSystem : public System
    {
    public:

        virtual ~IRenderSystem() {}

        virtual void registerEntity( Entity _entity ) = 0;
        virtual void unregisterEntity( Entity _entity ) = 0;
    };
}