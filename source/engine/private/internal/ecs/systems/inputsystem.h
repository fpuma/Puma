#pragma once

#include <engine/ecs/systems/iinputsystem.h>

namespace puma
{
    class InputSystem final : public IInputSystem
    {
    public:

        InputSystem();

        void uninit();
        void update( float _deltaTime );
        void prePhysicsUpdate( float _deltaTime ) {}
        void postPhysicsUpdate( float _deltaTime ) {}

        void queueRenderables( IRenderQueue& _renderQueue ) {}

        virtual void setProperties( SystemProperties _properties ) { m_systemProperties = _properties; }
        virtual SystemProperties getProperties() const { return m_systemProperties; }

        void registerEntity( Entity _entity );
        void unregisterEntity( Entity _entity );

    private:
#ifdef _DEBUG
        bool entityComponentCheck( Entity _entity );
#endif
        void init();


        std::set<Entity> m_entities;
        SystemProperties m_systemProperties;
    };
}