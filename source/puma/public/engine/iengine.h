#pragma once

#include <utils/graphics/dimensions.h>

namespace puma
{
    class ServiceContainer;

    class IEngine
    {
    public:
        virtual ~IEngine(){}

        static std::unique_ptr<IEngine> create();

        virtual void init( const Extent _windowExtent = { 1280,720,200,200 }, const char* _windowName = "Puma" ) = 0;
        virtual void uninit() = 0;

        virtual void update() = 0;
        virtual void render() = 0;

        virtual bool shouldQuit() const = 0;
    };
}