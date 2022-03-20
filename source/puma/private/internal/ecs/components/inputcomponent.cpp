#include "precompiledengine.h"

#include "internal/ecs/components/inputcomponent.h"

namespace puma
{
    void InputComponent::addInputMap( InputAction _inputAction, MousePositionInput _mousePositionInput )
    {
        m_inputMaps.insert( InputMap( _inputAction, _mousePositionInput ) );
    }

    void InputComponent::addInputMap( InputAction _inputAction, MouseButtonInput _mouseButtonInput )
    {
        m_inputMaps.insert( InputMap( _inputAction, _mouseButtonInput ) );
    }

    void InputComponent::addInputMap( InputAction _inputAction, MouseWheelInput _mouseWheelInput )
    {
        m_inputMaps.insert( InputMap( _inputAction, _mouseWheelInput ) );
    }

    void InputComponent::addInputMap( InputAction _inputAction, KeyboardInput _keyboardInput )
    {
        m_inputMaps.insert( InputMap( _inputAction, _keyboardInput ) );
    }
    
    void InputComponent::addInputMap( InputAction _inputAction, ControllerButtonInput _controllerButtonInput )
    {
        m_inputMaps.insert( InputMap( _inputAction, _controllerButtonInput ) );
    }

    void InputComponent::addInputMap( InputAction _inputAction, ControllerTriggerInput _controllerTriggerInput )
    {
        m_inputMaps.insert( InputMap( _inputAction, _controllerTriggerInput ) );
    }

    void InputComponent::addInputMap( InputAction _inputAction, ControllerJoystickInput _controllerJoystickInput )
    {
        m_inputMaps.insert( InputMap( _inputAction, _controllerJoystickInput ) );
    }

    void InputComponent::enableAction( InputAction _inputAction )
    {
        m_disabledActions.erase( _inputAction );
    }

    void InputComponent::disableAction( InputAction _inputAction )
    {
        m_disabledActions.insert( _inputAction );
    }

    bool InputComponent::isActionActive( InputAction _inputAction ) const
    {
        bool found = m_activeAction.find( _inputAction ) != m_activeAction.end();
        return (found);
    }

    InputActionExtraInfo InputComponent::getInputActionExtraInfo( InputAction _inputAction ) const
    {
        auto itFound = std::find_if( m_extraInfo.begin(), m_extraInfo.end(), [_inputAction]( const ExtraInfoData& extraInfoData )
        {
            return extraInfoData.inputAction == _inputAction;
        } );

        InputActionExtraInfo result;

        if ( itFound != m_extraInfo.end() )
        {
            result = itFound->extraInfo;
        }

        return result;
    }

    void InputComponent::evaluate()
    {
        m_activeAction.clear();
        m_extraInfo.clear();

        for ( const InputMap& inputMap : m_inputMaps )
        {
            InputEvalResult result = inputMap.evaluate();
            if ( result.active )
            {
                m_activeAction.insert( inputMap.getInputAction() );
                if ( result.hasExtraInfo )
                {
                    m_extraInfo.insert( { inputMap.getInputAction(), result.extraInfo } );
                }
            }
        }
    }
}