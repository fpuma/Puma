#pragma once

#include <modules/pina/entity.h>

#include <engine/ecs/systems/irendersystem.h>

#include <nina/texturemanager/texture.h>

namespace puma
{
    class IRenderQueue;

    class RenderSystem final : public IRenderSystem
    {
    public:

        RenderSystem();

        void queueRenderables( IRenderQueue& _renderQueue ) override;

        void registerEntity( Entity _entity ) override;
        void unregisterEntity( Entity _entity ) override;

    private:

#ifdef _DEBUG
        bool entityComponentCheck( Entity _entity );
#endif

        std::set<Entity> m_entities;
    };
}