#include <precompiledengine.h>

#include "shipmovementsystem.h"

#include <asteroids/fakedata/input/inputconfig.h>
#include <asteroids/components/shipcomponent.h>

#include <engine/ecs/components/iinputcomponent.h>
#include <engine/ecs/components/icollisioncomponent.h>
#include <engine/services/ecsservice.h>



ShipMovementSystem::ShipMovementSystem()
{
}

void ShipMovementSystem::postPhysicsUpdate( EntityProvider& _entityProvider, ComponentProvider& _componentProvider )
{
    IInputComponent* inputComponent = _componentProvider.getComponent<IInputComponent>( m_shipEntity );
    ShipComponent* shipComponent = _componentProvider.getComponent<ShipComponent>( m_shipEntity );
    
    if ( inputComponent->isActionActive( AsteroidsInputActions::MoveShip ) )
    {
        InputActionExtraInfo extraInfo = inputComponent->getInputActionExtraInfo( AsteroidsInputActions::MoveShip );

        Vec2 direction = { extraInfo.x, extraInfo.y };

        shipComponent->setDirection( direction.normalize() );
    }

    Vec2 currentForce = shipComponent->getCurrentForce();
    if ( currentForce.length() > 0.0f )
    {
        ICollisionComponent* collisionComponent = _componentProvider.getComponent<ICollisionComponent>( m_shipEntity );

        leo::IDynamicFrame* frame = collisionComponent->getDynamicFrame();

        frame->applyForceToCenter( currentForce );
    }
}