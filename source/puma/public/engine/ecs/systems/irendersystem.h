#pragma once

#include <pina/entity.h>
#include <engine/layers/isystem.h>

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

        virtual void registerEntity( pina::Entity _entity ) = 0;
        virtual void unregisterEntity( pina::Entity _entity ) = 0;
    };
}