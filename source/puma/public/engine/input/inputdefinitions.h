#pragma once

#include <engine/application/applicationdefinitions.h>
#include <utils/genericid.h>

namespace puma
{

    DECLARE_GENERIC_ID( InputAction, s32, kMaxS32 )

    enum InputModifier : size_t
    {
        InputModifier_LCTRL   = 0x01, 
        InputModifier_RCTRL   = 0x02, 
        InputModifier_LSHIFT  = 0x04, 
        InputModifier_RSHIFT  = 0x08, 
        InputModifier_LALT    = 0x10, 
        InputModifier_RALT    = 0x20, 
        InputModifier_NONE    = 0x40,
        InputModifier_IGNORE  = 0x80,
    };

    using ModifierBitmask = char;

    inline bool doModifiersMatch( const ModifierBitmask& modifiersA, const ModifierBitmask& modifiersB )
    {
        return (modifiersA == modifiersB) || (modifiersA | InputModifier_IGNORE) || (modifiersB | InputModifier_IGNORE);
    }

    enum class ControllerJoystick : NinaInputId
    {
        LEFT_STICK,
        RIGHT_STICK,
    };

    enum class InputState
    {
        Pressed,
        Released,
    };

    struct InputActionExtraInfo
    {
        float x = 0.0f;
        float y = 0.0f;
    };

    struct MousePositionInput
    {
        bool operator == ( const MousePositionInput& _other ) const
        {
            return doModifiersMatch( modifiers, _other.modifiers );
        }

        bool operator < ( const MousePositionInput& _other ) const
        {
            if ( modifiers != _other.modifiers ) { return modifiers < _other.modifiers; }
            return false;
        }

        ModifierBitmask modifiers = {};
    };

    struct MouseButtonInput
    {
        bool operator == ( const MouseButtonInput& _other ) const
        {
            bool modMatch = doModifiersMatch( modifiers, _other.modifiers );
            return (mouseButton == _other.mouseButton) && modMatch && (state == _other.state);
        }

        bool operator < ( const MouseButtonInput& _other ) const
        {
            if ( mouseButton != _other.mouseButton ) { return mouseButton < _other.mouseButton; }
            if ( modifiers != _other.modifiers ) { return modifiers < _other.modifiers; }
            if ( state != _other.state ) { return state < _other.state; }
            return false;
        }

        NinaMouseButton mouseButton = {};
        ModifierBitmask modifiers = {};
        InputState state = InputState::Pressed;
    };

    struct MouseWheelInput
    {
        bool operator == ( const MouseWheelInput& _other ) const
        {
            bool modMatch = doModifiersMatch( modifiers, _other.modifiers );
            return (mouseWheel == _other.mouseWheel) && modMatch;
        }

        bool operator < ( const MouseWheelInput& _other ) const
        {
            if ( mouseWheel != _other.mouseWheel ) { return mouseWheel < _other.mouseWheel; }
            if ( modifiers != _other.modifiers ) { return modifiers < _other.modifiers; }
            return false;
        }

        NinaMouseWheel mouseWheel = NinaMouseWheel::MW_IDLE;
        ModifierBitmask modifiers = {};
    };

    struct KeyboardInput
    {
        bool operator == ( const KeyboardInput& _other ) const
        {
            bool modMatch = doModifiersMatch( modifiers, _other.modifiers );
            return (keyboardKey == _other.keyboardKey) && modMatch && (state == _other.state);
        }

        bool operator < ( const KeyboardInput& _other ) const
        {
            if ( keyboardKey != _other.keyboardKey ) { return keyboardKey < _other.keyboardKey; }
            if ( modifiers != _other.modifiers ) { return modifiers < _other.modifiers; }
            if ( state != _other.state ) { return state < _other.state; }
            return false;
        }

        NinaKeyboardKey keyboardKey = {};
        ModifierBitmask modifiers = {};
        InputState state = InputState::Pressed;
    };

    struct ControllerButtonInput
    {
        bool operator == ( const ControllerButtonInput& _other ) const
        {
            return (controllerButton == _other.controllerButton) && (controllerId == _other.controllerId) && (state == _other.state);
        }

        bool operator < ( const ControllerButtonInput& _other ) const
        {
            if ( controllerButton != _other.controllerButton ) { return controllerButton < _other.controllerButton; }
            if ( controllerId != _other.controllerId ) { return controllerId < _other.controllerId; }
            if ( state != _other.state ) { return state < _other.state; }
            return false;
        }

        NinaControllerButton controllerButton = {};
        NinaControllerId controllerId = {};
        InputState state = InputState::Pressed;
    };

    struct ControllerTriggerInput
    {
        bool operator == ( const ControllerTriggerInput& _other ) const
        {
            return (controllerTrigger == _other.controllerTrigger) && (controllerId == _other.controllerId);
        }

        bool operator < ( const ControllerTriggerInput& _other ) const
        {
            if ( controllerTrigger != _other.controllerTrigger ) { return controllerTrigger < _other.controllerTrigger; }
            if ( controllerId != _other.controllerId ) { return controllerId < _other.controllerId; }
            return false;
        }

        NinaControllerTrigger controllerTrigger = {};
        NinaControllerId controllerId = {};
    };

    struct ControllerJoystickInput
    {
        bool operator == ( const ControllerJoystickInput& _other ) const
        {
            return (controllerJoystick == _other.controllerJoystick) && (controllerId == _other.controllerId);
        }

        bool operator < ( const ControllerJoystickInput& _other ) const
        {
            if ( controllerJoystick != _other.controllerJoystick ) { return controllerJoystick < _other.controllerJoystick; }
            if ( controllerId != _other.controllerId ) { return controllerId < _other.controllerId; }
            return false;
        }

        ControllerJoystick controllerJoystick = {};
        NinaControllerId controllerId = {};
    };

    struct InputEvalResult
    {
        bool active = false;
        bool hasExtraInfo = false;
        InputActionExtraInfo extraInfo;
    };
}