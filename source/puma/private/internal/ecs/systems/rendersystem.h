#pragma once

#include <pina/entity.h>

#include <engine/ecs/systems/irendersystem.h>

#include <nina/texturemanager/texture.h>

namespace puma
{
    class IRenderQueue;

    class RenderSystem final : public IRenderSystem
    {
    public:

        void onInit() override;
        void onUninit() override;

        void queueRenderables( IRenderQueue& _renderQueue ) override;

        void registerEntity( pina::Entity _entity ) override;
        void unregisterEntity( pina::Entity _entity ) override;

    private:

#ifdef _DEBUG
        bool entityComponentCheck( pina::Entity _entity );
#endif

        std::set<pina::Entity> m_entities;
    };
}