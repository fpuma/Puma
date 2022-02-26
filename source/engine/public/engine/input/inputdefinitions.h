#pragma once

#include <engine/application/applicationdefinitions.h>
#include <utils/genericid.h>

namespace puma
{
    DECLARE_GENERIC_ID( InputAction, s32, kMaxS32 )

    enum class InputModifier : AppInputId
    {
        NONE = 0,
        LCTRL = static_cast<AppInputId>(AppKeyboardKey::KB_LCTRL),
        RCTRL = static_cast<AppInputId>(AppKeyboardKey::KB_RCTRL),
        LSHIFT = static_cast<AppInputId>(AppKeyboardKey::KB_LSHIFT),
        RSHIFT = static_cast<AppInputId>(AppKeyboardKey::KB_RSHIFT),
        LALT = static_cast<AppInputId>(AppKeyboardKey::KB_LALT),
        RALT = static_cast<AppInputId>(AppKeyboardKey::KB_RALT),
    };

    enum class ControllerJoystick : AppInputId
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
            return (modifier == _other.modifier) && (state == _other.state);
        }

        bool operator < ( const MousePositionInput& _other ) const
        {
            if ( modifier != _other.modifier ) { return modifier < _other.modifier; }
            if ( state != _other.state ) { return state < _other.state; }
            return false;
        }

        InputModifier modifier = InputModifier::NONE;
        InputState state;
    };

    struct MouseButtonInput
    {
        bool operator == ( const MouseButtonInput& _other ) const
        {
            return (mouseButton == _other.mouseButton) && (modifier == _other.modifier) && (state == _other.state);
        }

        bool operator < ( const MouseButtonInput& _other ) const
        {
            if ( mouseButton != _other.mouseButton ) { return mouseButton < _other.mouseButton; }
            if ( modifier != _other.modifier ) { return modifier < _other.modifier; }
            if ( state != _other.state ) { return state < _other.state; }
            return false;
        }

        AppMouseButton mouseButton;
        InputModifier modifier = InputModifier::NONE;
        InputState state;
    };

    struct MouseWheelInput
    {
        bool operator == ( const MouseWheelInput& _other ) const
        {
            return (mouseWheel == _other.mouseWheel) && (modifier == _other.modifier);
        }

        bool operator < ( const MouseWheelInput& _other ) const
        {
            if ( mouseWheel != _other.mouseWheel ) { return mouseWheel < _other.mouseWheel; }
            if ( modifier != _other.modifier ) { return modifier < _other.modifier; }
            return false;
        }

        AppMouseWheel mouseWheel = AppMouseWheel::MW_IDLE;
        InputModifier modifier = InputModifier::NONE;
    };

    struct KeyboardInput
    {
        bool operator == ( const KeyboardInput& _other ) const
        {
            return (keyboardKey == _other.keyboardKey) && (modifier == _other.modifier) && (state == _other.state);
        }

        bool operator < ( const KeyboardInput& _other ) const
        {
            if ( keyboardKey != _other.keyboardKey ) { return keyboardKey < _other.keyboardKey; }
            if ( modifier != _other.modifier ) { return modifier < _other.modifier; }
            if ( state != _other.state ) { return state < _other.state; }
            return false;
        }

        AppKeyboardKey keyboardKey;
        InputModifier modifier = InputModifier::NONE;
        InputState state;
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

        AppControllerButton controllerButton;
        AppControllerId controllerId;
        InputState state;
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

        AppControllerTrigger controllerTrigger;
        AppControllerId controllerId;
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

        ControllerJoystick controllerJoystick;
        AppControllerId controllerId;
    };
}