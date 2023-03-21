#pragma once

#include <engine/layers/isystem.h>
#include <pina/entity.h>

#include <engine/utils/position.h>

using namespace puma;

namespace test
{
    class StaticStuffSystem : public ISystem
    {
    public:

        StaticStuffSystem();

        void onInit() override;

        void onUninit() override;

        void queueRenderables( IRenderQueue& _renderQueue ) override;

    private:

        ScreenPos m_screenPos;
        Position m_worldPosition;

        pina::Entity m_backgroundEntity;
    };
}