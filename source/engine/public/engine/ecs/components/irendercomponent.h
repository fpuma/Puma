#pragma once
#include <engine/ecs/base/icomponent.h>
#include <engine/resources/renderable.h>

namespace puma
{

    class Renderable;

    struct RenderSize
    {
        float x = 0.0f;
        float y = 0.0f;
    };

    class IRenderComponent : public IComponent
    {
    public:

        virtual ~IRenderComponent(){}

        virtual void setSize( const RenderSize& _size ) = 0;
        virtual RenderSize getSize() const = 0;

        virtual gfx::Texture getTexture() const = 0;
        virtual gfx::Extent getUVExtent() const = 0;

        virtual void setRenderable( const Renderable& _renderable ) = 0;
    };
}