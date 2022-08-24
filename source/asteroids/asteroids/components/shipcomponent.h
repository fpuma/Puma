#pragma once

#include <modules/pina/component.h>
#include <utils/geometry/vec2.h>

using namespace puma;

class ShipComponent : public Component
{
public:

    void setDirection( Vec2 _direction ) { m_currentForce = _direction * m_thrust; }
    Vec2 getCurrentForce() const { return m_currentForce; }

    void setThrust( float _thrust ) { m_thrust = _thrust; }
    float getThrust() const { return m_thrust; }

private:

    float m_thrust = 5000.0f;

    Vec2 m_currentForce;

};