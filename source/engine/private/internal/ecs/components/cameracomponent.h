#pragma once

#include <engine/ecs/components/icameracomponent.h>

namespace puma
{
    class CameraComponent final : public ICameraComponent
    {
    public:

        void enable() override { m_enabled = true; };
        void disable() override { m_enabled = false; };
        bool isEnabled() const override { return m_enabled; }


        float getMetersPerPixel() const override { return m_metersPerPixel; }
        void setMetersPerPixel( float _metersPerPixel ) override { m_metersPerPixel = _metersPerPixel; }

    private:

        float m_metersPerPixel = 0.1f;
        bool m_enabled = true;
    };
}