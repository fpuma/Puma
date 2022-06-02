#pragma once

namespace puma
{
    class IGame;

    class IEngine
    {
    public:
        virtual ~IEngine(){}

        static void run( std::unique_ptr<IGame>&& _game );
    };
}