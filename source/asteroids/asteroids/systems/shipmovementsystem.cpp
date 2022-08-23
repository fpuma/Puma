#include <precompiledengine.h>

#include "shipmovementsystem.h"

#include <asteroids/fakedata/input/inputconfig.h>
#include <asteroids/components/shipcomponent.h>

#include <engine/ecs/components/iinputcomponent.h>
#include <engine/ecs/components/icollisioncomponent.h>
#include <engine/services/ecsservice.h>



ShipMovementSystem::ShipMovementSystem()
{
    //m_systemProperties.updateBitMask = SystemUpdateFlag_PostPhysicsUpdate;
}

void ShipMovementSystem::postPhysicsUpdate( float _deltaTime )
{
    ComponentProvider* componentProvider = gComponents;
    IInputComponent* inputComponent = componentProvider->getComponent<IInputComponent>( m_shipEntity );
    ShipComponent* shipComponent = componentProvider->getComponent<ShipComponent>( m_shipEntity );
    
    if ( inputComponent->isActionActive( AsteroidsInputActions::MoveShip ) )
    {
        InputActionExtraInfo extraInfo = inputComponent->getInputActionExtraInfo( AsteroidsInputActions::MoveShip );

        Vec2 direction = { extraInfo.x, extraInfo.y };

        shipComponent->setDirection( direction.normalize() );
    }

    Vec2 currentForce = shipComponent->getCurrentForce();
    if ( currentForce.length() > 0.0f )
    {
        ICollisionComponent* collisionComponent = componentProvider->getComponent<ICollisionComponent>( m_shipEntity );

        leo::IDynamicFrame* frame = collisionComponent->getDynamicFrame();

        frame->applyForceToCenter( currentForce );
    }
}