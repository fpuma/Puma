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

        void registerInputListener() { m_inputQueue.registerInputListener(); }
        void unregisterInputListener() { m_inputQueue.unregisterInputListener(); }
        void updateWriteBuffer() { m_inputQueue.updateWriteBuffer(); }

    private:

        InputQueue m_inputQueue;
    };
}