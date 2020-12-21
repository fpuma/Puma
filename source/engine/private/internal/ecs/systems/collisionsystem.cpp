#include <precompiledengine.h>

#include "collisionsystem.h"

#include <internal/services/providersservice.h>
#include <internal/services/physicsservice.h>
#include <internal/ecs/base/providers/componentprovider.h>
#include <internal/ecs/base/providers/entityprovider.h>

#include <internal/ecs/components/collisioncomponent.h>
#include <internal/ecs/components/locationcomponent.h>

#include <physics/simulation/frames/iframe.h>
#include <physics/simulation/world/iworld.h>

namespace puma
{
    void CollisionSystem::init()
    {
        m_properties.updateBitMask = (SystemUpdateBitMask)SystemUpdateFlag::PostPhysicsUpdate;
                                   //| (SystemUpdateBitMask)SystemUpdateFlag::PrePhysicsUpdate;
    }

    void CollisionSystem::uninit()
    {
        assert( m_entities.empty() ); //Warning not all entities have been unregistered.
        m_entities.clear();
    }

    void CollisionSystem::registerEntity( Entity _entity, physics::FrameInfo _frameInfo )
    {
        assert( entityComponentCheck( _entity ) ); //This entity does not have the necessary components to be registered into this system

        ComponentProvider* componentProvider = gProviders->get<ComponentProvider>();

        assert( nullptr != componentProvider );

        physics::IWorld* world = gPhysics->getDefaultWorld();

        physics::FrameType frameType = _frameInfo.frameType;
        physics::FrameID frameId = physics::kInvalidPhysicsID;

        switch ( frameType )
        {
        case physics::FrameType::Dynamic:    frameId = world->addDynamicFrame( _frameInfo ); break;
        case physics::FrameType::Static:     frameId = world->addStaticFrame( _frameInfo ); break;
        case physics::FrameType::Kinematic:  frameId = world->addKinematicFrame( _frameInfo ); break;
        default: break;
        }

        CollisionComponent* collisionComponent = componentProvider->get<CollisionComponent>( _entity );
        collisionComponent->init( frameType, frameId );

        m_entities.emplace( _entity );
    }

    void CollisionSystem::unregisterEntity( Entity _entity )
    {
        assert( m_entities.find( _entity ) != m_entities.end() ); //This entity is not registered to this system

        m_entities.erase( _entity );
    }

    void CollisionSystem::postPhysicsUpdate( float _deltaTime )
    {
        ComponentProvider* componentProvider = gProviders->get<ComponentProvider>();

        for ( Entity entity : m_entities )
        {
            if ( !gProviders->get<EntityProvider>()->isEntityEnabled( entity ) ) continue;

            CollisionComponent* collisionComponent = componentProvider->get<CollisionComponent>( entity );

            if ( !collisionComponent->isEnabled() ) continue;

            LocationComponent* locationComponent = componentProvider->get<LocationComponent>( entity );

            Position pos = gPhysics->getFrame( collisionComponent->getFrameID() )->getPosition();
            locationComponent->setPosition( pos );
        }
    }

#ifdef _DEBUG
    bool CollisionSystem::entityComponentCheck( Entity _entity )
    {
        ComponentProvider* componentProvider = gProviders->get<ComponentProvider>();
        bool hasCollisionComponent = componentProvider->exists<CollisionComponent>( _entity );
        bool hasLocationComponent = componentProvider->exists<LocationComponent>( _entity );
        return ( hasCollisionComponent && hasLocationComponent );
    }
#endif
}