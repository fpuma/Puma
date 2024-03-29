#pragma once

#include <modules/nina/ninadefinitions.h>
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

        virtual void addRenderableTexture( const nina::Texture& _texture, const nina::TextureSample& _textureSample, const RenderSize& _renderSize, const Position& _position, const RotationRadians& _rotation, RenderLayer _renderLayer = {} ) = 0;
        virtual void addRenderableText( const std::string& _textToRender, const Color& _color, const Position& _position, RenderLayer _renderLayer = {} ) = 0;
        virtual void addRenderableShape( const Shape& _shape, const Color& _color, bool _solid, const Position& _position, const RotationRadians& _rotation, RenderLayer _renderLayer = {} ) = 0;

        virtual void addScreenRenderableTexture( const nina::Texture& _texture, const nina::TextureSample& _textureSample, const Extent& _screenExtent, const RotationRadians& _rotation, RenderLayer _renderLayer = {} ) = 0;
        virtual void addScreenRenderableText( const std::string& _textToRender, const Color& _color, const ScreenPos& _screenPos, RenderLayer _renderLayer = {} ) = 0;

        virtual void addDebugRenderableTexture( const nina::Texture& _texture, const nina::TextureSample& _textureSample, const RenderSize& _renderSize, const Position& _position, const RotationRadians& _rotation, RenderLayer _renderLayer = {} ) = 0;
        virtual void addDebugRenderableText( const std::string& _textToRender, const Color& _color, const Position& _position, RenderLayer _renderLayer = {} ) = 0;
        virtual void addDebugRenderableShape( const Shape& _shape, const Color& _color, bool _solid, const Position& _position, const RotationRadians& _rotation, RenderLayer _renderLayer = {} ) = 0;
        
        virtual void addDebugScreenRenderableTexture( const nina::Texture& _texture, const nina::TextureSample& _textureSample, const Extent& _screenExtent, const RotationRadians& _rotation, RenderLayer _renderLayer = {} ) = 0;
        virtual void addDebugScreenRenderableText( const std::string& _textToRender, const Color& _color, const ScreenPos& _screenPos, RenderLayer _renderLayer = {} ) = 0;

    };
}