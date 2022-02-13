#include "precompiledengine.h"
#include "inputmap.h"

#include <engine/application/applicationdefinitions.h>
#include <engine/services/iloggerservice.h>

namespace puma
{

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

    bool InputMap::evaluate() const
    {
        const AppInput* input = gInternalEngineApplication->getInput();

        assert( nullptr != input ); //Input was not initialized?

        bool result = true;

        switch ( m_deviceType )
        {
        case MouseButton:
        {
            const AppMouse& mouse = input->getMouse();
            const AppKeyboard& keyboard = input->getKeyboard();

            const auto& deviceInput = m_inputMap.mouseButton;

            if ( deviceInput.modifier != InputModifier::NONE )
            {
                result &= keyboard.keyState( static_cast<AppKeyboardKey>(deviceInput.modifier) );
            }

            switch ( deviceInput.state )
            {
            case InputState::Pressed: { result &= mouse.buttonPressed( deviceInput.mouseButton ); break; }
            case InputState::Released:{ result &= mouse.buttonReleased( deviceInput.mouseButton ); break; }
            default: 
                gLogger->error( "InputMap::evaluate - Invalid mouse button state." );
                break;
            }
            break;
        }
        case MouseWheel:
        {
            const AppMouse& mouse = input->getMouse();
            const AppKeyboard& keyboard = input->getKeyboard();

            const auto& deviceInput = m_inputMap.mouseWheel;

            if ( deviceInput.modifier != InputModifier::NONE )
            {
                result &= keyboard.keyState( static_cast<AppKeyboardKey>(deviceInput.modifier) );
            }

            if ( deviceInput.mouseWheel != AppMouseWheel::MW_IDLE )
            {
                result &= (mouse.getMouseWheelState() == deviceInput.mouseWheel);
            }

            break;
        }
        case KeyboardKey:
        {
            const AppKeyboard& keyboard = input->getKeyboard();

            const auto& deviceInput = m_inputMap.keyboard;

            if ( deviceInput.modifier != InputModifier::NONE )
            {
                result &= keyboard.keyState( static_cast<AppKeyboardKey>(deviceInput.modifier) );
            }

            switch ( deviceInput.state )
            {
            case InputState::Pressed: { result &= keyboard.keyPressed(  deviceInput.keyboardKey ); break; }
            case InputState::Released: { result &= keyboard.keyReleased( deviceInput.keyboardKey ); break; }
            default: 
                gLogger->error( "InputMap::evaluate - Invalid keyboard key state." );
                break;
            }

            break;
        }
        case ControllerButton:
        {
            const auto& deviceInput = m_inputMap.controllerButton;
            
            const AppController& controller = input->getController( deviceInput.controllerId );

            switch ( deviceInput.state )
            {
            case InputState::Pressed: { result &= controller.buttonPressed( deviceInput.controllerButton ); break; }
            case InputState::Released: { result &= controller.buttonReleased( deviceInput.controllerButton ); break; }
            default: 
                gLogger->error( "InputMap::evaluate - Invalid controller button state." );
                break;
            }

            break;
        }
        case ControllerTrigger:
        {
            const auto& deviceInput = m_inputMap.controllerTrigger;

            const AppController& controller = input->getController( deviceInput.controllerId );

            switch ( deviceInput.controllerTrigger )
            {
            case AppControllerTrigger::CT_LTRIGGER:
            {
                result &= controller.getLeftTrigger() > 0;
                //Store trigger value
                break;
            }
            case AppControllerTrigger::CT_RTRIGGER:
            {
                result &= controller.getRightTrigger() > 0;
                //Store trigger value
                break;
            }
            default:
                gLogger->error( "InputMap::evaluate - Invalid controller trigger." );
                break;
            }

            break;
        }
        default:
            break;
        }

        return result;
    }

    bool InputMap::operator == ( const InputMap& _other ) const
    {
        bool result = false;
        if ( (m_deviceType == _other.m_deviceType) && (m_inputAction == _other.m_inputAction))
        {
            switch ( m_deviceType )
            {
            case MouseButton: { result &= m_inputMap.mouseButton == _other.m_inputMap.mouseButton; break; }
            case MouseWheel: { result &= m_inputMap.mouseWheel == _other.m_inputMap.mouseWheel; break; }
            case KeyboardKey: { result &= m_inputMap.keyboard == _other.m_inputMap.keyboard; break; }
            case ControllerButton: { result &= m_inputMap.controllerButton == _other.m_inputMap.controllerButton; break; }
            case ControllerTrigger: { result &= m_inputMap.controllerTrigger == _other.m_inputMap.controllerTrigger; break; }
            default:
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
            case MouseButton: { result = m_inputMap.mouseButton < _other.m_inputMap.mouseButton; break; }
            case MouseWheel: { result = m_inputMap.mouseWheel < _other.m_inputMap.mouseWheel; break; }
            case KeyboardKey: { result = m_inputMap.keyboard < _other.m_inputMap.keyboard; break; }
            case ControllerButton: { result = m_inputMap.controllerButton < _other.m_inputMap.controllerButton; break; }
            case ControllerTrigger: { result = m_inputMap.controllerTrigger < _other.m_inputMap.controllerTrigger; break; }
            default:
                break;
            }
        }

        return result;
    }
}