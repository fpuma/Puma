#pragma once

#include <engine/ecs/base/icomponent.h>
#include <utils/geometry/vec2.h>

using namespace puma;

class ShipComponent : public IComponent
{
public:

    void setDirection( Vec2 _direction ) { m_currentForce = _direction * m_thrust; }
    Vec2 getCurrentForce() const { return m_currentForce; }

    void setThrust( float _thrust ) { m_thrust = _thrust; }
    float getThrust() const { return m_thrust; }

    void enable() override { m_enabled = true; }
    void disable() override { m_enabled = false; }
    bool isEnabled() const override { return m_enabled; }

private:

    bool m_enabled = true;

    float m_thrust = 5000.0f;

    Vec2 m_currentForce;

};