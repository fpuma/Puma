#pragma once
#include <engine/ecs/components/ilocationcomponent.h>

namespace puma
{
    class LocationComponent final : public ILocationComponent
    {
    public:

        Position getPosition() const override { return m_position; }
        void setPosition( const Position& _pos ) override { m_position = _pos; }

        void setRadiansRotation( float _angle ) override { m_radiansRotation = _angle; }
        float getRadiansRotation() const override { return m_radiansRotation; }

    private:
        Position m_position;
        float m_radiansRotation = 0.0f;
    };
}