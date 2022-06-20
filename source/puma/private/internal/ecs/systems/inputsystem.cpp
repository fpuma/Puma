#include "precompiledengine.h"

#include "inputsystem.h"

#include <engine/input/inputdefinitions.h>
#include <engine/services/iprovidersservice.h>
#include <internal/ecs/base/providers/componentprovider.h>
#include <internal/ecs/components/inputcomponent.h>
#include <internal/services/loggerservice.h>
#include <utils/formatstring.h>

namespace puma
{

    InputSystem::InputSystem()
    {
        init();
    }

    void InputSystem::uninit()
    {
        assert( m_entities.empty() ); //Warning not all entities have been unregistered.
        m_entities.clear();
    }

    void InputSystem::update( float _deltaTime )
    {
        bool readBufferUpdated = m_inputQueue.updateReadBuffer();
        
        //m_inputQueue.printInputs();
        ComponentProvider* componentProvider = gProviders->get<ComponentProvider>();
        for ( Entity entity : m_entities )
        {
            InputComponent* inputComponent = componentProvider->get<InputComponent>( entity );
            if (readBufferUpdated)
            {
                inputComponent->evaluate( *m_inputQueue.read() );
            }
            else
            {
                inputComponent->clearActiveActions();
            }
        }
    }

    void InputSystem::registerEntity( Entity _entity )
    {
        assert( entityComponentCheck( _entity ) ); //This entity does not have the necessary components to be registered into this system
        assert( m_entities.find( _entity ) == m_entities.end() ); //This entity has already been registered

        m_entities.emplace( _entity );
    }
    
    void InputSystem::unregisterEntity( Entity _entity )
    {
        if ( m_entities.find( _entity ) != m_entities.end() )
        {
            m_entities.erase(_entity);
        }
        else
        {
            gLogger->warning( "InputSystem::unregisterEntity - Trying to unregister an entity that has not been registered.");
        }
    }

#ifdef _DEBUG
    bool InputSystem::entityComponentCheck( Entity _entity )
    {
        ComponentProvider* componentProvider = gProviders->get<ComponentProvider>();
        return  componentProvider->exists<InputComponent>( _entity );
    }
#endif

    void InputSystem::init()
    {
        m_systemProperties.priority = 0;
        m_systemProperties.updateBitMask = SystemUpdateFlag_Update;
    }

}