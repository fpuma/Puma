#pragma once

#include <engine/input/inputdefinitions.h>
#include <internal/services/engineapplicationservice.h>

namespace puma
{
    class InputMap
    {
    public:

        InputMap() = delete;

        InputMap( InputAction _action, MouseButtonInput _mouseInput );
        InputMap( InputAction _action, MouseWheelInput _mouseWheelInput );
        InputMap( InputAction _action, KeyboardInput _keyboardInput );
        InputMap( InputAction _action, ControllerButtonInput _controllerButton );
        InputMap( InputAction _action, ControllerTriggerInput _controllerTrigger );

        bool operator == ( const InputMap& _other ) const;
        bool operator < ( const InputMap& _other ) const;

        bool evaluate() const;

        InputAction getInputAction() const { return m_inputAction; }

    private:

        enum
        {
            MouseButton,
            MouseWheel,
            KeyboardKey,
            ControllerButton,
            ControllerTrigger,
        }m_deviceType = KeyboardKey;

        union InternalInputMap
        {
            InternalInputMap() {}

            MouseButtonInput mouseButton;
            MouseWheelInput mouseWheel;
            KeyboardInput keyboard = {};
            ControllerButtonInput controllerButton;
            ControllerTriggerInput controllerTrigger;
        }m_inputMap;

        InputAction m_inputAction;
    };
}