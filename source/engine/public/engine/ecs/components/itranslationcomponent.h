#pragma once
#include <engine/ecs/base/icomponent.h>
#include <engine/utils/position.h>

namespace puma
{
    class ITranslationComponent : public IComponent
    {
    public:

        virtual void queueTranslation( Position _origin, Position _destination, float _speed ) = 0;

        virtual Position getDestination() const = 0;
        virtual float getSpeed() const = 0;
        virtual bool hasReachedDestination( const Position& _currentPosition ) const = 0;

        virtual bool isTranslationInProgress() const = 0;
        virtual void setTranslationFinished() = 0;
    };
}