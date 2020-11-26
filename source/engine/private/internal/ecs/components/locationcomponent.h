#pragma once
#include <engine/ecs/components/ilocationcomponent.h>

namespace puma
{
    class LocationComponent final : public ILocationComponent
    {
    public:

        void enable() override { m_enabled = true; };
        void disable() override { m_enabled = false; };
        bool isEnabled() const override { return m_enabled; }

        Position getPosition() const override { return m_position; }
        void setPosition( const Position& _pos ) override { m_position = _pos; }

        void setDegreesRotation( float _angle ) override { m_degreesRotation = _angle; }
        float getDegreesRotation() const override { return m_degreesRotation; }

    private:
        Position m_position;
        float m_degreesRotation = 0.0f;
        bool m_enabled = true;
    };
}