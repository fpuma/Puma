#pragma once

#include <modules/pina/system.h>
#include <modules/pina/entity.h>

using namespace puma;

namespace test
{
    class StaticStuffSystem : public System
    {
    public:

        StaticStuffSystem();

        void init();

        void uninit();

        void queueRenderables( IRenderQueue& _renderQueue ) override;

    private:

        Entity m_backgroundEntity;
    };
}