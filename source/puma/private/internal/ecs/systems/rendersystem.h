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
    };
}