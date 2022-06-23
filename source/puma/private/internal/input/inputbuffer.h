#pragma once

#include <engine/input/inputdefinitions.h>
#include <utils/containers/containedvector.h>

namespace puma
{
    class InputBuffer
    {
    public:

        void setMousePosition( const MousePositionInput&& _input, const InputActionExtraInfo&& _extraInfo );
        void addMouseButton( const MouseButtonInput&& _input );
        void addMouseWheelInput( const MouseWheelInput&& _input );
        void addKeyboardInput( const KeyboardInput&& _input );
        void addControllerButtonInput( const ControllerButtonInput&& _input );
        void setControllerTriggerInput( const ControllerTriggerInput&& _input, const InputActionExtraInfo&& _extraInfo );
        void setJoystickInput( const ControllerJoystickInput&& _input, const InputActionExtraInfo&& _extraInfo );

        InputEvalResult isActive ( const MousePositionInput& _input ) const;
        InputEvalResult isActive ( const MouseButtonInput& _input ) const;
        InputEvalResult isActive ( const MouseWheelInput& _input ) const;
        InputEvalResult isActive ( const KeyboardInput& _input ) const;
        InputEvalResult isActive ( const ControllerButtonInput& _input ) const;
        InputEvalResult isActive ( const ControllerTriggerInput& _input ) const;
        InputEvalResult isActive ( const ControllerJoystickInput& _input ) const;

        void clear();

        void printToLog() const;

    private:

        struct MousePositionData
        {
            MousePositionInput input;
            InputActionExtraInfo extraInfo;
        };

        struct ControllerTriggerData
        {
            ControllerTriggerInput input;
            InputActionExtraInfo extraInfo;
        };

        struct ControllerJoystickData
        {
            ControllerJoystickInput input;
            InputActionExtraInfo extraInfo;
        };

        ContainedVector<MousePositionData, 10> m_mousePositions;
        ContainedVector<MouseButtonInput,10> m_mouseButtons;
        ContainedVector<MouseWheelInput, 10> m_mouseWheel;
        ContainedVector<KeyboardInput, 10> m_keyboardKeys;
        ContainedVector<ControllerButtonInput, 10> m_controllerButtons;
        ContainedVector<ControllerTriggerData, 10> m_controllerTriggers;
        ContainedVector<ControllerJoystickData, 10> m_controllerJoysticks;

    };
}