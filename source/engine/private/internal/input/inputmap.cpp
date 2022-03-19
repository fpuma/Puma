#include "precompiledengine.h"
#include "inputmap.h"

#include <engine/application/applicationdefinitions.h>
#include <engine/services/iloggerservice.h>
#include <input/iinput.h>

namespace puma
{
    InputMap::InputMap( InputAction _action, MousePositionInput _mousePosition )
        : m_deviceType( MousePosition )
        , m_inputAction( _action )
    {
        m_inputMap.mousePosition = _mousePosition;
    }

    InputMap::InputMap( InputAction _action, MouseButtonInput _mouseInput )
        : m_deviceType( MouseButton )
        , m_inputAction( _action )
    {
        m_inputMap.mouseButton = _mouseInput;
    }

    InputMap::InputMap( InputAction _action, MouseWheelInput _mouseWheelInput )
        : m_deviceType( MouseWheel )
        , m_inputAction( _action )
    {
        m_inputMap.mouseWheel = _mouseWheelInput;
    }

    InputMap::InputMap( InputAction _action, KeyboardInput _keyboardInput )
        : m_deviceType( KeyboardKey )
        , m_inputAction( _action )
    {
        m_inputMap.keyboard = _keyboardInput;
    }

    InputMap::InputMap( InputAction _action, ControllerButtonInput _controllerButton )
        : m_deviceType( ControllerButton )
        , m_inputAction( _action )
    {
        m_inputMap.controllerButton = _controllerButton;
    }

    InputMap::InputMap( InputAction _action, ControllerTriggerInput _controllerTrigger )
        : m_deviceType( ControllerTrigger )
        , m_inputAction( _action )
    {
        m_inputMap.controllerTrigger = _controllerTrigger;
    }

    InputMap::InputMap( InputAction _action, ControllerJoystickInput _controllerJoystick )
        : m_deviceType( ControllerJoystick )
        , m_inputAction( _action )
    {
        m_inputMap.controllerJoystick = _controllerJoystick;
    }

    InputEvalResult InputMap::evaluate() const
    {
        const NinaInput* input = gInternalEngineApplication->getInput();

        assert( nullptr != input ); //Input was not initialized?

        InputEvalResult result;

        switch ( m_deviceType )
        {
        case MousePosition:
        {
            const NinaMouse& mouse = input->getMouse();
            result.active = mouse.wasMousePositionUpdated();
            if ( result.active )
            {
                result.hasExtraInfo = true;
                result.extraInfo = { static_cast<float>(mouse.getMousePosition().x), static_cast<float>(mouse.getMousePosition().y) };
            }
            break;
        }
        case MouseButton:
        {
            const NinaMouse& mouse = input->getMouse();
            const NinaKeyboard& keyboard = input->getKeyboard();

            const auto& deviceInput = m_inputMap.mouseButton;

            result.active = deviceInput.modifier != InputModifier::NONE ?
                            keyboard.keyState( static_cast<NinaKeyboardKey>(deviceInput.modifier) ) :
                            true;

            switch ( deviceInput.state )
            {
            case InputState::Pressed: { result.active &= mouse.buttonPressed( deviceInput.mouseButton ); break; }
            case InputState::Released:{ result.active &= mouse.buttonReleased( deviceInput.mouseButton ); break; }
            default: 
                gLogger->error( "InputMap::evaluate - Invalid mouse button state." );
                break;
            }
            break;
        }
        case MouseWheel:
        {
            const NinaMouse& mouse = input->getMouse();
            const NinaKeyboard& keyboard = input->getKeyboard();

            const auto& deviceInput = m_inputMap.mouseWheel;

            result.active = deviceInput.modifier != InputModifier::NONE ?
                            keyboard.keyState( static_cast<NinaKeyboardKey>(deviceInput.modifier) ) :
                            true;

            if ( deviceInput.mouseWheel != NinaMouseWheel::MW_IDLE )
            {
                result.active &= (mouse.getMouseWheelState() == deviceInput.mouseWheel);
            }

            break;
        }
        case KeyboardKey:
        {
            const NinaKeyboard& keyboard = input->getKeyboard();

            const auto& deviceInput = m_inputMap.keyboard;

            result.active = deviceInput.modifier != InputModifier::NONE ?
                            keyboard.keyState( static_cast<NinaKeyboardKey>(deviceInput.modifier) ) :
                            true;

            switch ( deviceInput.state )
            {
            case InputState::Pressed: { result.active &= keyboard.keyPressed(  deviceInput.keyboardKey ); break; }
            case InputState::Released: { result.active &= keyboard.keyReleased( deviceInput.keyboardKey ); break; }
            default: 
                gLogger->error( "InputMap::evaluate - Invalid keyboard key state." );
                break;
            }

            break;
        }
        case ControllerButton:
        {
            if ( input->getControllerCount() == 0 ) break;

            const auto& deviceInput = m_inputMap.controllerButton;
            
            const NinaController& controller = input->getController( deviceInput.controllerId );

            switch ( deviceInput.state )
            {
            case InputState::Pressed: { result.active = controller.buttonPressed( deviceInput.controllerButton ); break; }
            case InputState::Released: { result.active = controller.buttonReleased( deviceInput.controllerButton ); break; }
            default: 
                gLogger->error( "InputMap::evaluate - Invalid controller button state." );
                break;
            }

            break;
        }
        case ControllerTrigger:
        {
            if ( input->getControllerCount() == 0 ) break;

            const auto& deviceInput = m_inputMap.controllerTrigger;

            const NinaController& controller = input->getController( deviceInput.controllerId );

            switch ( deviceInput.controllerTrigger )
            {
            case NinaControllerTrigger::CT_LTRIGGER:
            {
                result.active = controller.wasLeftTriggerUpdated();
                if ( result.active )
                {
                    result.hasExtraInfo = true;
                    result.extraInfo = { controller.getLeftTrigger(), 0.0f };
                }
                break;
            }
            case NinaControllerTrigger::CT_RTRIGGER:
            {
                result.active = controller.wasRightTriggerUpdated();
                if ( result.active )
                {
                    result.hasExtraInfo = true;
                    result.extraInfo = { controller.getRightTrigger(), 0.0f };
                }
                break;
            }
            default:
                gLogger->error( "InputMap::evaluate - Invalid controller trigger." );
                break;
            }

            break;
        }
        case ControllerJoystick:
        {
            if ( input->getControllerCount() == 0 ) break;

            const auto& deviceInput = m_inputMap.controllerJoystick;

            const NinaController& controller = input->getController( deviceInput.controllerId );

            switch ( deviceInput.controllerJoystick )
            {
            case ControllerJoystick::LEFT_STICK:
            {
                result.active = controller.wasLeftJoystickUpdated();
                if ( result.active )
                {
                    result.hasExtraInfo = true;
                    result.extraInfo = { controller.getLeftJoystickPosition().x, controller.getLeftJoystickPosition().y };
                }
                break;
            }
            case ControllerJoystick::RIGHT_STICK:
            {
                result.active = controller.wasRightJoystickUpdated();
                if ( result.active )
                {
                    result.hasExtraInfo = true;
                    result.extraInfo = { controller.getRightJoystickPosition().x, controller.getRightJoystickPosition().y };
                }
                break;
            }
            default:
                gLogger->error( "InputMap::evaluate - Invalid controller joystick." );
                break;
            }
            break;
        }
        default:
            assert( false ); //DeviceType not yet supported
            break;
        }

        return { result };
    }

    bool InputMap::operator == ( const InputMap& _other ) const
    {
        bool result = false;
        if ( (m_deviceType == _other.m_deviceType) && (m_inputAction == _other.m_inputAction))
        {
            switch ( m_deviceType )
            {
            case MousePosition: { result &= m_inputMap.mousePosition == _other.m_inputMap.mousePosition; break; }
            case MouseButton: { result &= m_inputMap.mouseButton == _other.m_inputMap.mouseButton; break; }
            case MouseWheel: { result &= m_inputMap.mouseWheel == _other.m_inputMap.mouseWheel; break; }
            case KeyboardKey: { result &= m_inputMap.keyboard == _other.m_inputMap.keyboard; break; }
            case ControllerButton: { result &= m_inputMap.controllerButton == _other.m_inputMap.controllerButton; break; }
            case ControllerTrigger: { result &= m_inputMap.controllerTrigger == _other.m_inputMap.controllerTrigger; break; }
            case ControllerJoystick: { result &= m_inputMap.controllerJoystick == _other.m_inputMap.controllerJoystick; break; }
            default:
                assert( false ); //Invalid DeviceType
                break;
            }
        }
        return result;
    }

    bool InputMap::operator < ( const InputMap& _other ) const 
    { 
        bool result = false;
        if ( *this == _other )
        {
            return result;
        }

        if ( m_deviceType != _other.m_deviceType )
        {
            result = m_deviceType < _other.m_deviceType;
        }
        else if ( m_inputAction != _other.m_inputAction )
        {
            result = m_inputAction < _other.m_inputAction;
        }
        else
        {
            switch ( m_deviceType )
            {
            case MousePosition: { result = m_inputMap.mousePosition < _other.m_inputMap.mousePosition; break; }
            case MouseButton: { result = m_inputMap.mouseButton < _other.m_inputMap.mouseButton; break; }
            case MouseWheel: { result = m_inputMap.mouseWheel < _other.m_inputMap.mouseWheel; break; }
            case KeyboardKey: { result = m_inputMap.keyboard < _other.m_inputMap.keyboard; break; }
            case ControllerButton: { result = m_inputMap.controllerButton < _other.m_inputMap.controllerButton; break; }
            case ControllerTrigger: { result = m_inputMap.controllerTrigger < _other.m_inputMap.controllerTrigger; break; }
            case ControllerJoystick: { result = m_inputMap.controllerJoystick < _other.m_inputMap.controllerJoystick; break; }
            default:
                assert( false ); //Invalid DeviceType
                break;
            }
        }

        return result;
    }
}