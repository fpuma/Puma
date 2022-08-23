#pragma once

#include <engine/ecs/components/icameracomponent.h>

namespace puma
{
    class CameraComponent final : public ICameraComponent
    {
    public:

        float getMetersPerPixel() const override { return m_metersPerPixel; }
        void setMetersPerPixel( float _metersPerPixel ) override { m_metersPerPixel = _metersPerPixel; }

    private:

        float m_metersPerPixel = 0.1f;
    };
}