#include "precompiledengine.h"

#include "inputsystem.h"

#include <engine/input/inputdefinitions.h>
#include <engine/services/ecsservice.h>
#include <engine/services/systemsservice.h>
#include <internal/ecs/components/inputcomponent.h>
#include <internal/services/loggerservice.h>
#include <utils/formatstring.h>

namespace puma
{
    void InputSystem::onInit()
    {
        registerInputListener();

        gSystems->subscribeSystemUpdate<InputSystem>( SystemUpdateId::Update );
    }

    void InputSystem::onUninit()
    {
        unregisterInputListener();
        gSystems->unsubscribeSystemUpdate<InputSystem>( SystemUpdateId::Update );

        assert( m_entities.empty() ); //Warning not all entities have been unregistered.
        m_entities.clear();
    }

    void InputSystem::update( pina::EntityProvider& _entityProvider, pina::ComponentProvider& _componentProvider )
    {
        bool readBufferUpdated = m_inputQueue.updateReadBuffer();
        
        //m_inputQueue.printInputs();
        for (pina::Entity entity : m_entities )
        {
            InputComponent* inputComponent = _componentProvider.get<InputComponent>( entity );
            
            if (!_entityProvider.isEntityEnabled( entity ) ||
                !inputComponent->isEnabled())
            {
                inputComponent->clearActiveActions();
                continue;
            }

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

    void InputSystem::registerEntity( pina::Entity _entity )
    {
        assert( entityComponentCheck( _entity ) ); //This entity does not have the necessary components to be registered into this system
        assert( m_entities.find( _entity ) == m_entities.end() ); //This entity has already been registered

        m_entities.emplace( _entity );
    }
    
    void InputSystem::unregisterEntity( pina::Entity _entity )
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
    bool InputSystem::entityComponentCheck( pina::Entity _entity )
    {
        pina::ComponentProvider* componentProvider = gComponents;
        return  componentProvider->contains<InputComponent>( _entity );
    }
#endif

}