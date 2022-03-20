#pragma once
#include <engine/ecs/base/icomponent.h>
#include <engine/utils/renderdefinitions.h>

namespace puma
{
    
    using TextureInfoContainer = std::vector<TextureInfo>;

    class IRenderComponent : public IComponent
    {
    public:

        virtual ~IRenderComponent(){}

        virtual void addTextureInfo( TextureInfo _textureInfo ) = 0;

        virtual const TextureInfoContainer& getTextureInfoContainer() const = 0;
    };
}