#pragma once

#include <modules/nina/ninadefinitions.h>
#include <modules/pina/entity.h>

namespace puma
{

    DECLARE_GENERIC_ID(TextureId, size_t, (size_t)-1 )

    class IEngineApplication
    {
    public:

        virtual ~IEngineApplication() {}

        virtual nina::ITextureManager* getTextureManager() const = 0;

        virtual void setWindowSize( s32 _width, s32 _height ) = 0;
        virtual void setWindowPosition( s32 _x, s32 _y ) = 0;
        virtual void setWindowTitle( const char* _title ) = 0;
        virtual void setCameraEntity( Entity _cameraEntity ) = 0;
    };
}