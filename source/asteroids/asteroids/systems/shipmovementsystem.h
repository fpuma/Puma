#pragma once

#include <engine/ecs/base/entity.h>
#include <engine/ecs/base/isystem.h>

using namespace puma;

class ShipMovementSystem : public ISystem
{
public:

    ShipMovementSystem();
    
    void uninit() override {}
    void update( float _deltaTime ) {}
    void prePhysicsUpdate( float _deltaTime ) {}
    void postPhysicsUpdate( float _deltaTime );

    void queueRenderables( IRenderQueue& _renderQueue ) {};

    void setProperties( SystemProperties _properties ) { m_systemProperties = _properties; }
    SystemProperties getProperties() const { return m_systemProperties; }


    void setShipEntity( Entity _entity ) { m_shipEntity = _entity; }

private:

    SystemProperties m_systemProperties;
    Entity m_shipEntity;
};