#pragma once
#include <engine/ecs/base/icomponent.h>
#include <engine/resources/renderable.h>

namespace puma
{
    class Renderable;

    class IRenderComponent : public IComponent
    {
    public:

        virtual ~IRenderComponent(){}

        virtual void setSize( const RenderSize& _size ) = 0;
        virtual RenderSize getSize() const = 0;

        virtual app::Texture getTexture() const = 0;
        virtual Extent getSampledExtent() const = 0;

        virtual void setRenderable( const Renderable& _renderable ) = 0;
    };
}