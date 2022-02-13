#include "precompiledengine.h"

#include "internal/ecs/components/inputcomponent.h"

namespace puma
{
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

    void InputComponent::evaluate()
    {
        m_activeAction.clear();

        for ( const InputMap& inputMap : m_inputMaps )
        {
            if ( inputMap.evaluate() )
            {
                m_activeAction.insert( inputMap.getInputAction() );
            }
        }
    }
}