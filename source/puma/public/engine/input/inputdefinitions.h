#pragma once

#include <engine/external/ninadefinitions.h>
#include <utils/genericid.h>

namespace puma
{

    DECLARE_GENERIC_ID( InputAction, s32, kMaxS32 )

    enum InputModifier : size_t
    {
        InputModifier_NONE    = 0x00,
        InputModifier_LCTRL   = 0x01, 
        InputModifier_RCTRL   = 0x02, 
        InputModifier_LSHIFT  = 0x04, 
        InputModifier_RSHIFT  = 0x08, 
        InputModifier_LALT    = 0x10, 
        InputModifier_RALT    = 0x20, 
        InputModifier_IGNORE  = 0x40,
    };

    using ModifierBitmask = char;

    inline bool doModifiersMatch( const ModifierBitmask& modifiersA, const ModifierBitmask& modifiersB )
    {
        return (modifiersA == modifiersB) || (modifiersA & InputModifier_IGNORE) || (modifiersB & InputModifier_IGNORE);
    }

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

        nina::MouseButton mouseButton = {};
        ModifierBitmask modifiers = {};
        nina::InputButtonEvent state = nina::InputButtonEvent::Pressed;
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

        nina::MouseWheelState mouseWheel = nina::MouseWheelState::MW_IDLE;
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

        nina::KeyboardKey keyboardKey = {};
        ModifierBitmask modifiers = {};
        nina::InputButtonEvent state = nina::InputButtonEvent::Pressed;
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

        nina::ControllerButton controllerButton = {};
        nina::ControllerId controllerId = {};
        nina::InputButtonEvent state = nina::InputButtonEvent::Pressed;
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

        nina::ControllerTrigger controllerTrigger = {};
        nina::ControllerId controllerId = {};
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

        nina::ControllerJoystick controllerJoystick = {};
        nina::ControllerId controllerId = {};
    };

    struct InputEvalResult
    {
        bool active = false;
        bool hasExtraInfo = false;
        InputActionExtraInfo extraInfo;
    };
}