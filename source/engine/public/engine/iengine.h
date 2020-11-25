#pragma once

namespace puma
{

    class ServiceContainer;

    class IEngine
    {
    public:
        virtual ~IEngine(){}

        static std::unique_ptr<IEngine> create();

        virtual void init() = 0;
        virtual void uninit() = 0;

        virtual void update() = 0;
        virtual void render() = 0;

        virtual bool shouldQuit() const = 0;
    };
}