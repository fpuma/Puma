#pragma once

#include <engine/ecs/systems/iinputsystem.h>
#include <internal/input/inputqueue.h>

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

        void registerEntity( Entity _entity ) override;
        void unregisterEntity( Entity _entity ) override;

        void registerInputListener() { m_inputQueue.registerInputListener(); }
        void unregisterInputListener() { m_inputQueue.unregisterInputListener(); }
        void updateWriteBuffer() { m_inputQueue.updateWriteBuffer(); }

    private:
#ifdef _DEBUG
        bool entityComponentCheck( Entity _entity );
#endif

        std::set<Entity> m_entities;

        InputQueue m_inputQueue;
    };
}