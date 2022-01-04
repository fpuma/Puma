#pragma once

#include <engine/application/applicationdefinitions.h>
#include <engine/utils/position.h>
#include <engine/utils/renderdefinitions.h>

namespace puma
{
    class Shape;

    constexpr int kMaxRenderablesCount = 1000;

    class IRenderQueue
    {
    public:

        virtual ~IRenderQueue() {}

        virtual void addRenderableTexture( const AppTexture& _texture, const AppTextureSample& _textureSample, const RenderSize& _renderSize, const Position& _position, const RotationDegrees& _rotation, bool _debug = false ) = 0;
        virtual void addRenderableText(const std::string& _textToRender, const Color& _color, const Position& _position, bool _debug = false ) = 0;
        virtual void addRenderableShape(const Shape& _shape, const Color& _color, bool _solid, const Position& _position, const RotationDegrees& _rotation, bool _debug = false ) = 0;
    };
}