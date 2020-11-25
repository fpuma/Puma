#include <precompiledengine.h>

#include <internal/ecs/components/translationcomponent.h>

namespace puma
{
    void TranslationComponent::queueTranslation( Position _origin, Position _destination, float _speed )
    {
        m_destination = _destination;
        m_initialDifference = _destination - _origin;
        m_speed = _speed;
        m_translationInProgress = true;
    }

    bool TranslationComponent::hasReachedDestination( const Position& _currentPosition ) const
    {
        Position currentDifference = m_destination - _currentPosition;

        return m_initialDifference.dot( currentDifference ) <= 0;
    }
}