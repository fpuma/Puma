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
    }

    void InputSystem::update( pina::EntityProvider& _entityProvider, pina::ComponentProvider& _componentProvider )
    {
        bool readBufferUpdated = m_inputQueue.updateReadBuffer();
        
        auto entities = gECS->getEntitesByComponents<InputComponent>();

        //m_inputQueue.printInputs();
        for (pina::Entity entity : entities)
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
}