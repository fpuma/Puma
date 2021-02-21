#pragma once

#include <engine/application/applicationdefinitions.h>

namespace puma
{
    class IEngineApplication
    {
    public:

        static std::unique_ptr<IEngineApplication> create();

        virtual ~IEngineApplication() {}

        virtual void init( Extent _windowExtent, const char* _windowName ) = 0;
        virtual void uninit() = 0;
        virtual void update() = 0;
        virtual AppWindow* getWindow() const = 0;
        virtual AppTextureManager* getTextureManager() const = 0;
        virtual AppInput* getInput() const = 0;
    };
}