#pragma once

#include <engine/ecs/components/iinputcomponent.h>
#include <internal/input/inputmap.h>

namespace puma
{
    class InputComponent final : public IInputComponent
    {
    public:

        void enable() override { m_enabled = true; }
        void disable() override { m_enabled = false; }
        bool isEnabled() const override { return m_enabled; }

        void addInputMap( InputAction _inputAction, MouseButtonInput _mouseButtonInput ) override;
        void addInputMap( InputAction _inputAction, MouseWheelInput _mouseWheelInput ) override;
        void addInputMap( InputAction _inputAction, KeyboardInput _keyboardInput ) override;
        void addInputMap( InputAction _inputAction, ControllerButtonInput _controllerButtonInput ) override;
        void addInputMap( InputAction _inputAction, ControllerTriggerInput _controllerTriggerInput ) override;

        void enableAction( InputAction _inputAction ) override;
        void disableAction( InputAction _inputAction ) override;

        bool isActionActive( InputAction _inputAction ) const override;

        void evaluate();

    private:

        std::set<InputAction> m_activeAction;

        std::set<InputMap> m_inputMaps;
        std::set<InputAction> m_disabledActions;

        bool m_enabled = true;
    };
}