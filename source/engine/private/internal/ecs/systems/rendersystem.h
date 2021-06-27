#pragma once

#include <engine/ecs/base/entity.h>

#include <engine/ecs/systems/irendersystem.h>

#include <texturemanager/texture.h>

namespace puma
{
    class RenderSystem final : public IRenderSystem
    {
    public:

        RenderSystem();

        void init() override;
        void uninit() override;

        void update             ( float _deltaTime ) override {};
        void prePhysicsUpdate( float _deltaTime ) override {};
        void postPhysicsUpdate( float _deltaTime ) override {};
        void queueRenderables( QueueRenderableCallback _queueRenderableCallback ) override;

        void setProperties( SystemProperties _properties ) override { m_properties = _properties; }
        SystemProperties getProperties() const override { return m_properties; }

        void registerEntity( Entity _entity ) override;
        void unregisterEntity( Entity _entity ) override;

    private:

#ifdef _DEBUG
        bool entityComponentCheck( Entity _entity );
#endif

        SystemProperties m_properties;

        std::set<Entity> m_entities;
    };
}