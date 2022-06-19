#include "precompiledengine.h"
#include "inputmap.h"

#include <engine/application/applicationdefinitions.h>
#include <engine/services/iloggerservice.h>
//#include <input/iinput.h>
#include <internal/input/inputbuffer.h>
//#include <internal/services/engineapplicationservice.h>
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

    InputEvalResult InputMap::evaluate( const InputBuffer& _inputBuffer ) const
    {
        InputEvalResult result;

        switch ( m_deviceType )
        {
        case MousePosition:
        {
            result = _inputBuffer.isActive( m_inputMap.mousePosition );
            break;
        }
        case MouseButton:
        {
            result = _inputBuffer.isActive( m_inputMap.mouseButton );
            break;
        }
        case MouseWheel:
        {
            result = _inputBuffer.isActive( m_inputMap.mouseWheel );
            break;
        }
        case KeyboardKey:
        {
            result = _inputBuffer.isActive( m_inputMap.keyboard );
            break;
        }
        case ControllerButton:
        {
            result = _inputBuffer.isActive( m_inputMap.controllerButton );
            break;
        }
        case ControllerTrigger:
        {
            result = _inputBuffer.isActive( m_inputMap.controllerTrigger );
            break;
        }
        case ControllerJoystick:
        {
            result = _inputBuffer.isActive( m_inputMap.controllerJoystick );
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