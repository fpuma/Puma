#pragma once

#include <engine/igame.h>

namespace test
{
    class Test : public puma::IGame
    {
    public:

        void init() override;
        void update(float _deltaTime) override;
        void uninit() override;
    };
}



