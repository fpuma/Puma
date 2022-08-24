#pragma once

#include <modules/pina/entity.h>
#include <modules/pina/system.h>

using namespace puma;

class ShipMovementSystem : public System
{
public:

    ShipMovementSystem();
    
    void postPhysicsUpdate( EntityProvider& _entityProvider, ComponentProvider& _componentProvider ) override;

    void setShipEntity( Entity _entity ) { m_shipEntity = _entity; }

private:

    Entity m_shipEntity;
};