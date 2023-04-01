#pragma once

#include <pina/component.h>
#include <utils/geometry/vec2.h>

namespace test
{
    class MoveDirectionComponent final : public puma::pina::Component
    {
    public:

        void setDirection( puma::Vec2 _value ) { m_direction = _value; }
        puma::Vec2 getDirection() const { return m_direction; }

    private:

        puma::Vec2 m_direction;
    };
}