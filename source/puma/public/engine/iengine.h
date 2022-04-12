#pragma once

namespace puma
{
    class IGame;

    class IEngine
    {
    public:
        virtual ~IEngine(){}

        static std::unique_ptr<IEngine> create();

        virtual void run( std::unique_ptr<IGame>&& _game ) = 0;
    };
}