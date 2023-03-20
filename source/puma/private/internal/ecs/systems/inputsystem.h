#pragma once

#include <engine/ecs/systems/iinputsystem.h>
#include <internal/input/inputqueue.h>

namespace puma
{
    class InputSystem final : public IInputSystem
    {
    public:

        void onInit() override;
        void onUninit() override;

        void update( pina::EntityProvider& _entityProvider, pina::ComponentProvider& _componentProvider ) override;

        void registerEntity( pina::Entity _entity ) override;
        void unregisterEntity( pina::Entity _entity ) override;

        void registerInputListener() { m_inputQueue.registerInputListener(); }
        void unregisterInputListener() { m_inputQueue.unregisterInputListener(); }
        void updateWriteBuffer() { m_inputQueue.updateWriteBuffer(); }

    private:

#ifdef _DEBUG
        bool entityComponentCheck( pina::Entity _entity );
#endif

        std::set<pina::Entity> m_entities;

        InputQueue m_inputQueue;
    };
}