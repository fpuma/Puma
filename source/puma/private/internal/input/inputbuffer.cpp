#include "precompiledengine.h"

#include "inputbuffer.h"

#include <internal/services/loggerservice.h>
#include <nina/input/iinput.h>

namespace puma
{
    void InputBuffer::setMousePosition( const MousePositionInput&& _input, const InputActionExtraInfo&& _extraInfo )
    {
        auto itFoundMousePos = std::find_if( m_mousePositions.begin(), m_mousePositions.end(), [&]( const MousePositionData& data ) 
            {
                return data.input == _input;
            } );

        if (m_mousePositions.end() != itFoundMousePos)
        {
            itFoundMousePos->extraInfo = _extraInfo;
        }
        else
        {
            m_mousePositions.push_back( { _input, _extraInfo } );
        }
    }

    void InputBuffer::addMouseButton( const MouseButtonInput&& _input )
    {
        m_mouseButtons.push_back( _input );
    }

    void InputBuffer::addMouseWheelInput( const MouseWheelInput&& _input )
    {
        m_mouseWheel.push_back( _input );
    }

    void InputBuffer::addKeyboardInput( const KeyboardInput&& _input )
    {
        m_keyboardKeys.push_back( _input );
    }

    void InputBuffer::addControllerButtonInput( const ControllerButtonInput&& _input )
    {
        m_controllerButtons.push_back( _input );
    }

    void InputBuffer::setControllerTriggerInput( const ControllerTriggerInput&& _input, const InputActionExtraInfo&& _extraInfo )
    {
        auto itFoundTrigger = std::find_if( m_controllerTriggers.begin(), m_controllerTriggers.end(), [&]( const ControllerTriggerData& data )
            {
                return data.input == _input;
            });

        if ( m_controllerTriggers.end() != itFoundTrigger )
        {
            itFoundTrigger->extraInfo = _extraInfo;
        }
        else
        {
            m_controllerTriggers.push_back( { _input, _extraInfo } );
        }
    }

    void InputBuffer::setJoystickInput( const ControllerJoystickInput&& _input, const InputActionExtraInfo&& _extraInfo )
    {
        auto itFoundJoystick = std::find_if( m_controllerJoysticks.begin(), m_controllerJoysticks.end(), [&]( const ControllerJoystickData& data )
            {
                return data.input == _input;
            });
        if (m_controllerJoysticks.end() != itFoundJoystick)
        {
            if (_extraInfo.x > 0.0f)
            {
                itFoundJoystick->extraInfo.x = _extraInfo.x;
            }
            else
            {
                itFoundJoystick->extraInfo.y = _extraInfo.y;
            }
        }
        else
        {
            m_controllerJoysticks.push_back( { _input, _extraInfo } );
        }
    }

    //////////////////////////////////////////////////////////////////////////////

    InputEvalResult InputBuffer::isActive( const MousePositionInput& _input ) const
    {
        InputEvalResult result;
        auto itFoundInput = std::find_if( m_mousePositions.begin(), m_mousePositions.end(), [&]( const MousePositionData& data )
            {
                return data.input == _input;
            } );

        result.active = itFoundInput != m_mousePositions.end();
        result.hasExtraInfo = true;
        result.extraInfo = itFoundInput->extraInfo;
        return result;
    }

    InputEvalResult InputBuffer::isActive( const MouseButtonInput& _input ) const
    {
        InputEvalResult result;
        auto itFoundInput = std::find( m_mouseButtons.begin(), m_mouseButtons.end(), _input );
        result.active = itFoundInput != m_mouseButtons.end();
        return result;
    }

    InputEvalResult InputBuffer::isActive( const MouseWheelInput& _input ) const
    {
        InputEvalResult result;
        auto itFoundInput = std::find( m_mouseWheel.begin(), m_mouseWheel.end(), _input );
        result.active = itFoundInput != m_mouseWheel.end();
        return result;
    }

    InputEvalResult InputBuffer::isActive( const KeyboardInput& _input ) const
    {
        InputEvalResult result;
        auto itFoundInput = std::find( m_keyboardKeys.begin(), m_keyboardKeys.end(), _input );
        result.active = itFoundInput != m_keyboardKeys.end();
        return result;
    }

    InputEvalResult InputBuffer::isActive( const ControllerButtonInput& _input ) const
    {
        InputEvalResult result;
        auto itFoundInput = std::find( m_controllerButtons.begin(), m_controllerButtons.end(), _input );
        result.active = itFoundInput != m_controllerButtons.end();
        return result;
    }

    InputEvalResult InputBuffer::isActive( const ControllerTriggerInput& _input ) const
    {
        InputEvalResult result;
        auto itFoundInput = std::find_if( m_controllerTriggers.begin(), m_controllerTriggers.end(), [&]( const ControllerTriggerData& data )
            {
                return data.input == _input;
            } );

        result.active = itFoundInput != m_controllerTriggers.end();
        result.hasExtraInfo = true;
        result.extraInfo = itFoundInput->extraInfo;
        return result;
    }

    InputEvalResult InputBuffer::isActive( const ControllerJoystickInput& _input ) const
    {
        InputEvalResult result;
        auto itFoundInput = std::find_if( m_controllerJoysticks.begin(), m_controllerJoysticks.end(), [&]( const ControllerJoystickData& data )
            {
                return data.input == _input;
            } );

        result.active = itFoundInput != m_controllerJoysticks.end();
        result.hasExtraInfo = true;
        result.extraInfo = itFoundInput->extraInfo;
        return result;
    }

    void InputBuffer::clear()
    {
        m_mousePositions.clear();
        m_mouseButtons.clear();
        m_mouseWheel.clear();
        m_keyboardKeys.clear();
        m_controllerButtons.clear();
        m_controllerTriggers.clear();
        m_controllerJoysticks.clear();
    }

    void InputBuffer::printToLog() const
    {
        for (const KeyboardInput& kbInput : m_keyboardKeys)
        {
            const char* keyName = nina::IInput::getInputName( kbInput.keyboardKey );
            const char* keyState = kbInput.state == NinaInputButtonEvent::Pressed ? "PRESSED" : "RELEASED";
            gInternalLogger->info( formatString( "%s - %s", keyName, keyState ).c_str() );
        }

        for (const MouseButtonInput& mbInput : m_mouseButtons)
        {
            const char* buttonName = nina::IInput::getInputName( mbInput.mouseButton );
            const char* buttonState = mbInput.state == NinaInputButtonEvent::Pressed ? "PRESSED" : "RELEASED";
            gInternalLogger->info( formatString( "%s - %s", buttonName, buttonState ).c_str() );
        }

        for (const ControllerJoystickData& cjData : m_controllerJoysticks)
        {
            const ControllerJoystickInput& cjInput = cjData.input;
            const char* joystickName = cjInput.controllerJoystick == NinaControllerJoystick::CJ_LSTICK ? "LEFT" : "RIGHT";
            gInternalLogger->info( formatString( "Controller <%d> - %s Joystick - %.3f | %.3f", cjInput.controllerId, joystickName, cjData.extraInfo.x, cjData.extraInfo.y ).c_str() );
        }
    }
}