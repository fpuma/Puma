#pragma once

#include <engine/external/ninadefinitions.h>
#include <engine/ecs/base/entity.h>

namespace puma
{
    class IEngineApplication
    {
    public:

        virtual ~IEngineApplication() {}

        virtual NinaTextureManager* getTextureManager() const = 0;

        virtual void setWindowSize( s32 _width, s32 _height ) = 0;
        virtual void setWindowPosition( s32 _x, s32 _y ) = 0;
        virtual void setWindowTitle( const char* _title ) = 0;
        virtual void setCameraEntity( Entity _cameraEntity ) = 0;
    };
}