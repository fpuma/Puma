#pragma once

#include <pina/entity.h>
#include <engine/flow/system.h>

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

        virtual void registerEntity( pina::Entity _entity ) = 0;
        virtual void unregisterEntity( pina::Entity _entity ) = 0;
    };
}