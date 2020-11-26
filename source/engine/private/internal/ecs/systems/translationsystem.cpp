#include <precompiledengine.h>

#include <internal/ecs/systems/translationsystem.h>

#include <internal/ecs/base/providers/componentprovider.h>

#include <internal/services/providersservice.h>
#include <internal/ecs/components/locationcomponent.h>
#include <internal/ecs/components/translationcomponent.h>


namespace puma
{
    void TranslationSystem::internalUpdate(ComponentProvider* _componentProvider, Entity _entity, float _deltaTime )
    {
        TranslationComponent* translationComponent = _componentProvider->get<TranslationComponent>( _entity );

        if ( translationComponent->isTranslationInProgress() )
        {
            LocationComponent* locationComponent = _componentProvider->get<LocationComponent>( _entity );

            bool destinationReached = translationComponent->hasReachedDestination( locationComponent->getPosition() );

            if ( destinationReached )
            {
                translationComponent->setTranslationFinished();
            }
            else
            {
                Position currentDiff = translationComponent->getDestination() - locationComponent->getPosition();

                float diffX = std::abs( currentDiff.x );
                float diffY = std::abs( currentDiff.y );
                float sumXY = diffX + diffY;

                float xProportion = (float)currentDiff.x / (float)sumXY;
                float yProportion = (float)currentDiff.y / (float)sumXY;

                float xTranslation = (xProportion * _deltaTime * (float) translationComponent->getSpeed());
                float yTranslation = (yProportion * _deltaTime * (float) translationComponent->getSpeed());

                Position translation = { xTranslation, yTranslation };

                Position newPosition = locationComponent->getPosition() + translation;

                locationComponent->setPosition( newPosition );
            }

        }
    }

#ifdef _DEBUG
    bool TranslationSystem::entityComponentCheck( Entity _entity )
    {
        ComponentProvider* componentProvider = gProviders->get<ComponentProvider>();
        const TranslationComponent* translationComponent = componentProvider->get<TranslationComponent>( _entity );
        const LocationComponent* locationComponent = componentProvider->get<LocationComponent>( _entity );
        return (nullptr != translationComponent) && (nullptr != locationComponent);
    }
#endif
}