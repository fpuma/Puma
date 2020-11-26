#pragma once
#include <engine/ecs/base/entity.h>
#include <engine/ecs/components/itranslationcomponent.h>
#include <engine/utils/position.h>

namespace puma
{
    class TranslationComponent final : public ITranslationComponent
    {
    public:

        void enable() override { m_enabled = true; };
        void disable() override { m_enabled = false; };
        bool isEnabled() const override { return m_enabled; }


        void queueTranslation( Position _origin, Position _destination, float _speed ) override;

        Position getDestination() const override { return m_destination; }
        float getSpeed() const override { return m_speed; }
        bool hasReachedDestination( const Position& _currentPosition ) const override;

        bool isTranslationInProgress() const override { return m_translationInProgress; }
        void setTranslationFinished() override { m_translationInProgress = false; }

    private:
        Position m_destination;
        Position m_initialDifference;
        float m_speed = 0;

        bool m_translationInProgress = false;
        bool m_enabled = true;
    };
}