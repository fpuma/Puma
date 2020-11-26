#pragma once

#include <engine/ecs/base/entity.h>

#include <engine/ecs/systems/irendersystem.h>

#include <graphics/graphicdefinitions.h>
#include <graphics/texture.h>

namespace puma
{

    class RenderSystem final : public IRenderSystem
    {
    public:

        void init() override;
        void uninit() override;

        void update( float _deltaTime ) override {}
        void prePhysicsUpdate( float _deltaTime ) override {}
        void postPhysicsUpdate( float _deltaTime ) override;

        void setProperties( SystemProperties _properties ) override { m_properties = _properties; }
        SystemProperties getProperties() const { return m_properties; }

        void render() const;

        void setCameraEntity( Entity _cameraEntity );

        void registerEntity( Entity _entity ) override;

        void unregisterEntity( Entity _entity ) override;

    private:

#ifdef _DEBUG
        bool entityComponentCheck( Entity _entity );
#endif

        SystemProperties m_properties;

        Entity m_cameraEntity = kInvalidEntity;
        std::set<Entity> m_entities;

        struct TextureToRenderInfo
        {
            gfx::Texture texture;
            gfx::Extent uvExtent;
            gfx::Extent screenExtent;
            float rotationDegrees;
        };

        TextureToRenderInfo m_texturesToRender[kConcurrentTexturePool];
        u32 m_texturesToRenderCount = 0;
    };
}