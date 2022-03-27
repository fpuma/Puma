#pragma once

#include <engine/ecs/base/isystem.h>
#include <engine/ecs/base/entity.h>

using namespace puma;

namespace test
{
    class StaticStuffSystem : public ISystem
    {
    public:

        StaticStuffSystem();

        void init();

        void uninit() override;
        void update( float _deltaTime ) override {};
        void prePhysicsUpdate( float _deltaTime ) override {};
        void postPhysicsUpdate( float _deltaTime ) override {};

        void queueRenderables( IRenderQueue& _renderQueue ) override;

        void setProperties( SystemProperties _properties ) override { m_systemProperties = _properties; }
        SystemProperties getProperties() const override { return m_systemProperties; }

    private:
        SystemProperties m_systemProperties;

        Entity m_backgroundEntity;
    };
}