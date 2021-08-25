#pragma once

#include <engine/utils/position.h>
#include <texturemanager/texture.h>
#include <texturemanager/texturedefinitions.h>
#include <utils/graphics/dimensions.h>

namespace puma
{
    class IRenderable
    {
    public:

        virtual ~IRenderable() {}

        virtual void render() = 0;
    };
}