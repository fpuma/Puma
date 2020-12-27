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
    void CollisionSystem::init( physics::Vec2 _gravity )
    {
        m_properties.updateBitMask = (SystemUpdateBitMask)SystemUpdateFlag::PostPhysicsUpdate;
                                   //| (SystemUpdateBitMask)SystemUpdateFlag::PrePhysicsUpdate;

        m_worldId = gPhysics->addWorld( _gravity );
    }

    void CollisionSystem::uninit()
    {
        assert( m_entities.empty() ); //Warning not all entities have been unregistered.
        m_entities.clear();
        gPhysics->removeWorld( m_worldId );
    }

    void CollisionSystem::registerEntity( Entity _entity, physics::FrameInfo _frameInfo, physics::FrameType _frameType )
    {
        assert( entityComponentCheck( _entity ) ); //This entity does not have the necessary components to be registered into this system

        ComponentProvider* componentProvider = gProviders->get<ComponentProvider>();

        assert( nullptr != componentProvider );

        physics::IWorld* world = gPhysics->getWorld( m_worldId );

        physics::FrameID frameId = physics::kInvalidPhysicsID;

        switch ( _frameType )
        {
        case physics::FrameType::Dynamic:    frameId = world->addDynamicFrame( _frameInfo ); break;
        case physics::FrameType::Static:     frameId = world->addStaticFrame( _frameInfo ); break;
        case physics::FrameType::Kinematic:  frameId = world->addKinematicFrame( _frameInfo ); break;
        default: break;
        }

        CollisionComponent* collisionComponent = componentProvider->get<CollisionComponent>( _entity );
        collisionComponent->init( _frameType, frameId );

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
            bool shouldUpdate = gProviders->get<EntityProvider>()->isEntityEnabled( entity );
            CollisionComponent* collisionComponent = componentProvider->get<CollisionComponent>( entity );
            shouldUpdate = shouldUpdate && collisionComponent->isEnabled();

            physics::IFrame* physicsFrame = gPhysics->getFrame( collisionComponent->getFrameID() );

            if ( shouldUpdate )
            {
                LocationComponent* locationComponent = componentProvider->get<LocationComponent>( entity );

                Position pos = physicsFrame->getPosition();
                locationComponent->setPosition( pos );
                locationComponent->setDegreesRotation( -physicsFrame->getAngle() );
            }
            else
            {
                physicsFrame->disable();
            }
        }
    }

    void CollisionSystem::setGravity( physics::Vec2 _gravity )
    {
        gPhysics->getWorld( m_worldId )->setGravity( _gravity );
    }

    physics::Vec2 CollisionSystem::getGravity()
    {
        return gPhysics->getWorld( m_worldId )->getGravity();
    }

    void CollisionSystem::setCollisionCompatibility( const physics::CollisionCompatibility& _collisionCompatibility )
    {
        gPhysics->getWorld( m_worldId )->setCollisionCompatibility( _collisionCompatibility );
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