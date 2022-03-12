#pragma once

#include <engine/ecs/base/icomponent.h>
#include <utils/geometry/vec2.h>

namespace test
{
    class MoveDirectionComponent final : public puma::IComponent
    {
    public:

        void enable() { m_enabled = true; }
        void disable() { m_enabled = false; }
        bool isEnabled() const override { return m_enabled; }

        void setDirection( puma::Vec2 _value ) { m_direction = _value; }
        puma::Vec2 getDirection() const { return m_direction; }

    private:

        puma::Vec2 m_direction;

        bool m_enabled = true;
    };
}