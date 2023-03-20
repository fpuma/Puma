#pragma once
#include <pina/component.h>
#include <engine/utils/renderdefinitions.h>

namespace puma
{
    
    using TextureInfoContainer = std::vector<TextureInfo>;

    class IRenderComponent : public pina::Component
    {
    public:

        virtual ~IRenderComponent(){}

        virtual void addTextureInfo( TextureInfo _textureInfo ) = 0;

        virtual const TextureInfoContainer& getTextureInfoContainer() const = 0;
    };
}