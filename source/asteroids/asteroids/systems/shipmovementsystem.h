#pragma once

#include <modules/pina/entity.h>
#include <modules/pina/system.h>

using namespace puma;

class ShipMovementSystem : public System
{
public:

    ShipMovementSystem();
    
    void update( float _deltaTime ) {}
    void prePhysicsUpdate( float _deltaTime ) {}
    void postPhysicsUpdate( float _deltaTime );

    void queueRenderables( IRenderQueue& _renderQueue ) {};

    void setShipEntity( Entity _entity ) { m_shipEntity = _entity; }

private:

    Entity m_shipEntity;
};