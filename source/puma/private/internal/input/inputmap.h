#pragma once

#include <engine/input/inputdefinitions.h>

namespace puma
{
    class InputBuffer;

    class InputMap
    {
    public:

        InputMap() = delete;

        InputMap( InputAction _action, MousePositionInput _mousePosition );
        InputMap( InputAction _action, MouseButtonInput _mouseInput );
        InputMap( InputAction _action, MouseWheelInput _mouseWheelInput );
        InputMap( InputAction _action, KeyboardInput _keyboardInput );
        InputMap( InputAction _action, ControllerButtonInput _controllerButton );
        InputMap( InputAction _action, ControllerTriggerInput _controllerTrigger );
        InputMap( InputAction _action, ControllerJoystickInput _controllerJoystick );

        bool operator == ( const InputMap& _other ) const;
        bool operator < ( const InputMap& _other ) const;

        InputEvalResult evaluate(const InputBuffer& _inputBuffer) const;

        InputAction getInputAction() const { return m_inputAction; }

    private:

        enum
        {
            MousePosition,
            MouseButton,
            MouseWheel,
            KeyboardKey,
            ControllerButton,
            ControllerTrigger,
            ControllerJoystick,
        }m_deviceType = KeyboardKey;

        union InternalInputMap
        {
            InternalInputMap() {}

            MousePositionInput mousePosition;
            MouseButtonInput mouseButton;
            MouseWheelInput mouseWheel;
            KeyboardInput keyboard = {};
            ControllerButtonInput controllerButton;
            ControllerTriggerInput controllerTrigger;
            ControllerJoystickInput controllerJoystick;
        }m_inputMap;

        InputAction m_inputAction;
    };
}