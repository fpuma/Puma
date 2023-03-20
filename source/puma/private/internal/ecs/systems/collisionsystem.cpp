#include <precompiledengine.h>

#include "collisionsystem.h"

#include <engine/services/ecsservice.h>
#include <pina/componentprovider.h>
#include <pina/entityprovider.h>
#include <internal/services/physicsservice.h>

#include <internal/ecs/components/collisioncomponent.h>
#include <internal/ecs/components/locationcomponent.h>

#include <internal/physics/collisionlistener.h>

#include <internal/renderer/renderqueue.h>

#include <leo/simulation/frames/iframe.h>
#include <leo/simulation/world/iworld.h>

#define PHYSICS_DEBUG_RENDER

namespace puma
{
    void CollisionSystem::onInit()
    {
        assert( !m_worldId.isValid() ); //Initializing CollisionSystem for the second time

        m_worldId = gPhysics->addWorld( { 0.0f,0.0f } );

        setCollisionListener( std::make_unique<CollisionListener>() );
        gSystems->subscribeSystemUpdate<CollisionSystem>( SystemUpdateId::PostPhysics );
        gSystems->subscribeSystemUpdate<CollisionSystem>( SystemUpdateId::QueueRenderables );

#ifdef PHYSICS_DEBUG_RENDER
        std::unique_ptr<PhysicsDebugDraw> physicsDebugDraw = std::make_unique<PhysicsDebugDraw>();
        physicsDebugDraw->dbgShapesPtr = &m_debugShapes;

        leo::IWorld* world = gPhysics->getWorld( m_worldId );
        world->setDebugDraw( std::move(physicsDebugDraw) );
#endif
    }

    void CollisionSystem::onUninit()
    {
        gSystems->unsubscribeSystemUpdate<CollisionSystem>( SystemUpdateId::PostPhysics );
        gSystems->unsubscribeSystemUpdate<CollisionSystem>( SystemUpdateId::QueueRenderables );

        assert( m_entities.empty() ); //Warning not all entities have been unregistered.
        m_entities.clear();
        if ( m_worldId.isValid() )
        {
            gPhysics->removeWorld( m_worldId );
        }
    }

    void CollisionSystem::registerEntity( pina::Entity _entity, leo::FrameInfo _frameInfo, leo::FrameType _frameType )
    {
        assert( entityComponentCheck( _entity ) ); //This entity does not have the necessary components to be registered into this system

        pina::ComponentProvider* componentProvider = gComponents;

        assert( nullptr != componentProvider );

        leo::IWorld* world = gPhysics->getWorld( m_worldId );

        leo::FrameID frameId;

        switch ( _frameType )
        {
        case leo::FrameType::Dynamic:    frameId = world->addDynamicFrame( _frameInfo ); break;
        case leo::FrameType::Static:     frameId = world->addStaticFrame( _frameInfo ); break;
        case leo::FrameType::Kinematic:  frameId = world->addKinematicFrame( _frameInfo ); break;
        default: assert( false ); break;
        }

        CollisionComponent* collisionComponent = componentProvider->get<CollisionComponent>( _entity );
        collisionComponent->init( _frameType, frameId );

        m_entities.emplace( _entity );
    }

    void CollisionSystem::unregisterEntity( pina::Entity _entity )
    {
        assert( m_entities.find( _entity ) != m_entities.end() ); //This entity is not registered to this system

        leo::IWorld* world = gPhysics->getWorld( m_worldId );
        pina::ComponentProvider* componentProvider = gComponents;
        CollisionComponent* collisionComponent = componentProvider->get<CollisionComponent>( _entity );

        leo::FrameID frameToRemove = collisionComponent->getFrameID();

        assert( nullptr != collisionComponent );

        collisionComponent->uninit();
        world->removeFrame( frameToRemove );

        m_entities.erase( _entity );
    }

    void CollisionSystem::postPhysicsUpdate( pina::EntityProvider& _entityProvider, pina::ComponentProvider& _componentProvider )
    {
        for ( pina::Entity entity : m_entities )
        {
            bool shouldUpdate = _entityProvider.isEntityEnabled( entity );
            CollisionComponent* collisionComponent = _componentProvider.get<CollisionComponent>( entity );
            shouldUpdate = shouldUpdate && collisionComponent->isEnabled();

            if ( shouldUpdate )
            {
                leo::IFrame* physicsFrame = gPhysics->getFrame( collisionComponent->getFrameID() );
                LocationComponent* locationComponent = _componentProvider.get<LocationComponent>( entity );

                Position pos = { physicsFrame->getPosition().x, physicsFrame->getPosition().y };
                locationComponent->setPosition( pos );
                locationComponent->setRadiansRotation( physicsFrame->getAngle() );
            }
        }

#ifdef PHYSICS_DEBUG_RENDER
        if ( m_debugDraw )
        {
            leo::IWorld* world = gPhysics->getWorld( m_worldId );
            m_debugShapes.clear();
            world->debugDraw();
        }
#endif

    }

    void CollisionSystem::queueRenderables( IRenderQueue& _renderQueue )
    {
#ifdef PHYSICS_DEBUG_RENDER
        if ( m_debugDraw )
        {
            for ( const PhysicsDebugShape& dbgShape : m_debugShapes )
            {
                _renderQueue.addDebugRenderableShape( dbgShape.shape, dbgShape.color, dbgShape.solid, { 0.0f, 0.0f }, 0.0f );
            }

            pina::ComponentProvider* componentProvider = gComponents;
            for ( const pina::Entity& entity : m_entities )
            {
                CollisionComponent* collisionComponent = componentProvider->get<CollisionComponent>( entity );
                LocationComponent* locationComponent = componentProvider->get<LocationComponent>( entity );


                Vec2 lv;
                switch ( collisionComponent->getFrameType() )
                {
                case leo::FrameType::Dynamic: lv = collisionComponent->getDynamicFrame()->getLinearVelocity(); break;
                case leo::FrameType::Kinematic: lv = collisionComponent->getKinematicFrame()->getLinearVelocity(); break;
                default: break;
                }

                if ( lv.length() > 0.0f )
                {
                    _renderQueue.addDebugRenderableText( formatString( "LV: %.2f, %.2f", lv.x, lv.y ), Color::Red(), locationComponent->getPosition() );
                }
            }
        }
#endif
    }

    void CollisionSystem::setGravity( Vec2 _gravity )
    {
        gPhysics->getWorld( m_worldId )->setGravity( _gravity );
    }

    Vec2 CollisionSystem::getGravity()
    {
        return gPhysics->getWorld( m_worldId )->getGravity();
    }

    void CollisionSystem::setCollisionCompatibility( const leo::CollisionCompatibility& _collisionCompatibility )
    {
        gPhysics->getWorld( m_worldId )->setCollisionCompatibility( _collisionCompatibility );
    }

    void CollisionSystem::setCollisionListener( std::unique_ptr<leo::ICollisionListener>&& _collisionListener )
    {
        gPhysics->getWorld( m_worldId )->setCollisionListener( std::move( _collisionListener ) );
    }

    const leo::UserCollisionData CollisionSystem::getUserCollisionData( leo::FramePartID _framePartId ) const
    {
        leo::IFramePart* framePart = gPhysics->getFramePart( _framePartId );
        assert( nullptr != framePart );
        return framePart->getUserData();
    }

#ifdef _DEBUG
    bool CollisionSystem::entityComponentCheck( pina::Entity _entity )
    {
        pina::ComponentProvider* componentProvider = gComponents;
        bool hasCollisionComponent = componentProvider->contains<CollisionComponent>( _entity );
        bool hasLocationComponent = componentProvider->contains<LocationComponent>( _entity );
        return ( hasCollisionComponent && hasLocationComponent );
    }
#endif

    namespace
    {
        Color floatToIntColor( leo::RGBA _color )
        {
            return { (u8)(_color.r * 255), (u8)(_color.g * 255), (u8)(_color.b * 255), (u8)(_color.a * 255) };
        }
    }

    void CollisionSystem::PhysicsDebugDraw::renderPolygon( const std::vector<Vec2>&& _vertices, const leo::RGBA&& _color )
    {
        PhysicsDebugShape physicsDbgShape;
        physicsDbgShape.color = floatToIntColor( _color );
        physicsDbgShape.solid = false;

        Polygon polygon;
        std::transform( _vertices.begin(), _vertices.end(), std::back_inserter( polygon.vertices ), [&](const Vec2& point)
        {
            return point;
        } );

        
        physicsDbgShape.shape.setAsPolygon( polygon );
        dbgShapesPtr->push_back( physicsDbgShape );
    }

    void CollisionSystem::PhysicsDebugDraw::renderSolidPolygon( const std::vector<Vec2>&& _vertices, const leo::RGBA&& _color )
    {
        PhysicsDebugShape physicsDbgShape;
        physicsDbgShape.color = floatToIntColor( _color );
        physicsDbgShape.solid = true;

        Polygon polygon;
        std::transform( _vertices.begin(), _vertices.end(), std::back_inserter( polygon.vertices ), [&]( const Vec2& point )
        {
            return point;
        } );

        physicsDbgShape.shape.setAsPolygon( polygon );
        dbgShapesPtr->push_back( physicsDbgShape );
    }

    void CollisionSystem::PhysicsDebugDraw::renderCircle( const Vec2&& _center, float _radius, const leo::RGBA&& _color )
    {
        PhysicsDebugShape physicsDbgShape;
        physicsDbgShape.color = floatToIntColor( _color );
        physicsDbgShape.solid = false;

        Circle circle;
        circle.center = _center;
        circle.radius = _radius;

        physicsDbgShape.shape.setAsCircle( circle );
        dbgShapesPtr->push_back( physicsDbgShape );
    }

    void CollisionSystem::PhysicsDebugDraw::renderSolidCircle( const Vec2&& _center, float _radius, const leo::RGBA&& _color )
    {
        PhysicsDebugShape physicsDbgShape;
        physicsDbgShape.color = floatToIntColor( _color );
        physicsDbgShape.solid = true;

        Circle circle;
        circle.center = _center;
        circle.radius = _radius;

        physicsDbgShape.shape.setAsCircle( circle );
        dbgShapesPtr->push_back( physicsDbgShape );
    }

    void CollisionSystem::PhysicsDebugDraw::renderSegment( const Vec2&& _point1, const Vec2&& _point2, const leo::RGBA&& _color )
    {
        PhysicsDebugShape physicsDbgShape;
        physicsDbgShape.color = floatToIntColor( _color );

        Chain chain;
        chain.points.push_back( _point1 );
        chain.points.push_back( _point2 );

        physicsDbgShape.shape.setAsChain( chain );
        dbgShapesPtr->push_back( physicsDbgShape );
    }

}

