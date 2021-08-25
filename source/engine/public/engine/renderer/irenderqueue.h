#pragma once

#include <engine/application/applicationdefinitions.h>
#include <engine/utils/position.h>
#include <engine/utils/renderdefinitions.h>

namespace puma
{
    class IRenderQueue
    {
    public:

        virtual ~IRenderQueue() {}

        virtual void addRenderableTexture( AppTexture _texture, AppTextureSample _textureSample, RenderSize _renderSize, Position _position, RotationDegrees _rotation ) = 0;
        virtual void addRenderableText() = 0;
        virtual void addRenderableShape() = 0;
    };
}