#pragma once

#include <engine/ecs/base/entity.h>

#include <engine/ecs/systems/irendersystem.h>

#include <application/commondefinitions.h>
#include <texturemanager/texture.h>

namespace puma
{
    struct TextureToRenderInfo
    {
        app::Texture texture;
        app::Extent uvExtent;
        app::Extent screenExtent;
        float rotationDegrees;
    };

    using TexturesToRenderContainer = std::array<TextureToRenderInfo, kConcurrentTexturePool>;
    
    class RenderSystem final : public IRenderSystem
    {
    public:

        void init() override;
        void uninit() override;

        void update             ( float _deltaTime ) override {};
        void prePhysicsUpdate   ( float _deltaTime ) override;
        void postPhysicsUpdate  ( float _deltaTime ) override;

        void setProperties( SystemProperties _properties ) override { m_properties = _properties; }
        SystemProperties getProperties() const override { return m_properties; }
        
        void    setCameraEntity( Entity _cameraEntity );
        Entity  getCameraEntity() const override { return m_cameraEntity; }

        void registerEntity( Entity _entity ) override;
        void unregisterEntity( Entity _entity ) override;
        
        void render() const;

    private:

#ifdef _DEBUG
        bool entityComponentCheck( Entity _entity );
#endif

        SystemProperties m_properties;

        Entity m_cameraEntity = kInvalidEntity;
        std::set<Entity> m_nonPhysicalEntities;
        std::set<Entity> m_physicalEntities;

        TexturesToRenderContainer m_texturesToRender;
        u32 m_texturesToRenderCount = 0;
    };
}