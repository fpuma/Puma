#include <precompiledengine.h>

#include "collisionsystem.h"

#include <internal/services/providersservice.h>
#include <internal/services/physicsservice.h>
#include <internal/ecs/base/providers/componentprovider.h>
#include <internal/ecs/base/providers/entityprovider.h>

#include <internal/ecs/components/collisioncomponent.h>
#include <internal/ecs/components/locationcomponent.h>

#include <internal/renderer/renderqueue.h>

#include <physics/simulation/frames/iframe.h>
#include <physics/simulation/world/iworld.h>

//#define PHYSICS_DEBUG_RENDER

namespace puma
{
    void CollisionSystem::init( Vec2 _gravity )
    {
        m_properties.updateBitMask = (SystemUpdateBitMask)SystemUpdateFlag::PostPhysicsUpdate
                                   | (SystemUpdateBitMask)SystemUpdateFlag::QueueRenderables;

        m_worldId = gPhysics->addWorld( _gravity );

#ifdef PHYSICS_DEBUG_RENDER
        std::unique_ptr<PhysicsDebugDraw> physicsDebugDraw = std::make_unique<PhysicsDebugDraw>();
        physicsDebugDraw->dbgShapesPtr = &m_debugShapes;

        physics::IWorld* world = gPhysics->getWorld( m_worldId );
        world->setDebugDraw( std::move(physicsDebugDraw) );
#endif
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
        default: assert( false ); break;
        }

        CollisionComponent* collisionComponent = componentProvider->get<CollisionComponent>( _entity );
        collisionComponent->init( _frameType, frameId );

        m_entities.emplace( _entity );
    }

    void CollisionSystem::unregisterEntity( Entity _entity )
    {
        assert( m_entities.find( _entity ) != m_entities.end() ); //This entity is not registered to this system

        physics::IWorld* world = gPhysics->getWorld( m_worldId );
        ComponentProvider* componentProvider = gProviders->get<ComponentProvider>();
        CollisionComponent* collisionComponent = componentProvider->get<CollisionComponent>( _entity );

        physics::FrameID frameToRemove = collisionComponent->getFrameID();

        assert( nullptr != collisionComponent );

        collisionComponent->uninit();
        world->removeFrame( frameToRemove );

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

                Position pos = { physicsFrame->getPosition().x, physicsFrame->getPosition().y, 0.0f };
                locationComponent->setPosition( pos );
                locationComponent->setDegreesRotation( physicsFrame->getAngle() );
            }
            else
            {
                physicsFrame->disable();
            }
        }

#ifdef PHYSICS_DEBUG_RENDER
        physics::IWorld* world = gPhysics->getWorld( m_worldId );
        m_debugShapes.clear();
        world->debugDraw();
#endif

    }

    void CollisionSystem::queueRenderables( IRenderQueue& _renderQueue )
    {
#ifdef PHYSICS_DEBUG_RENDER
        for ( const PhysicsDebugShape& dbgShape : m_debugShapes )
        {
            _renderQueue.addRenderableShape( dbgShape.shape, dbgShape.color, dbgShape.solid, { 0.0f, 0.0f, 0.0f }, 0.0f, true );
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

    namespace
    {
        Color floatToIntColor( physics::RGBA _color )
        {
            return { (u8)(_color.r * 255), (u8)(_color.g * 255), (u8)(_color.b * 255), (u8)(_color.a * 255) };
        }
    }

    void CollisionSystem::PhysicsDebugDraw::renderPolygon( const std::vector<Vec2>&& _vertices, const physics::RGBA&& _color )
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

    void CollisionSystem::PhysicsDebugDraw::renderSolidPolygon( const std::vector<Vec2>&& _vertices, const physics::RGBA&& _color )
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

    void CollisionSystem::PhysicsDebugDraw::renderCircle( const Vec2&& _center, float _radius, const physics::RGBA&& _color )
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

    void CollisionSystem::PhysicsDebugDraw::renderSolidCircle( const Vec2&& _center, float _radius, const physics::RGBA&& _color )
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

    void CollisionSystem::PhysicsDebugDraw::renderSegment( const Vec2&& _point1, const Vec2&& _point2, const physics::RGBA&& _color )
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

