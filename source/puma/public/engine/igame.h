#pragma once

namespace puma
{
    class IGame
    {
    public:
        virtual ~IGame() {}
        virtual void init() = 0;
        virtual void update( float _deltaTime ) = 0;
        virtual void uninit() = 0;
    };
}