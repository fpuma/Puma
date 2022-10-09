#pragma once

#include <modules/pina/system.h>
#include <modules/pina/entity.h>

#include <engine/utils/position.h>

using namespace puma;

namespace test
{
    class StaticStuffSystem : public System
    {
    public:

        StaticStuffSystem();

        void onInit() override;

        void onUninit() override;

        void queueRenderables( IRenderQueue& _renderQueue ) override;

    private:

        ScreenPos m_screenPos;
        Position m_worldPosition;

        Entity m_backgroundEntity;
    };
}