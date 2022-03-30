#include <precompiledengine.h>

#include "shipmovementsystem.h"

#include <asteroids/fakedata/input/inputconfig.h>
#include <asteroids/components/shipcomponent.h>

#include <engine/ecs/base/providers/icomponentprovider.h>
#include <engine/ecs/components/iinputcomponent.h>
#include <engine/ecs/components/icollisioncomponent.h>
#include <engine/services/iprovidersservice.h>



ShipMovementSystem::ShipMovementSystem()
{
    m_systemProperties.updateBitMask = SystemUpdateFlag_PostPhysicsUpdate;
}

void ShipMovementSystem::postPhysicsUpdate( float _deltaTime )
{
    IComponentProvider* componentProvider = gProviders->get<IComponentProvider>();
    IInputComponent* inputComponent = componentProvider->get<IInputComponent>( m_shipEntity );
    ShipComponent* shipComponent = componentProvider->get<ShipComponent>( m_shipEntity );
    
    if ( inputComponent->isActionActive( AsteroidsInputActions::MoveShip ) )
    {
        InputActionExtraInfo extraInfo = inputComponent->getInputActionExtraInfo( AsteroidsInputActions::MoveShip );

        Vec2 direction = { extraInfo.x, extraInfo.y };

        shipComponent->setDirection( direction.normalize() );
    }

    Vec2 currentForce = shipComponent->getCurrentForce();
    if ( currentForce.length() > 0.0f )
    {
        ICollisionComponent* collisionComponent = componentProvider->get<ICollisionComponent>( m_shipEntity );

        LeoDynamicFrame* frame = collisionComponent->getDynamicFrame();

        frame->applyForceToCenter( currentForce );
    }
}