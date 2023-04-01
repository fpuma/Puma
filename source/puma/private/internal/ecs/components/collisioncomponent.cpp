#include <precompiledengine.h>

#include <internal/ecs/components/collisioncomponent.h>
#include <internal/ecs/systems/collisionsystem.h>
#include <internal/services/physicsservice.h>

#include <leo/simulation/frames/iframe.h>
#include <leo/simulation/world/iworld.h>

#include <engine/services/systemsservice.h>

namespace puma
{

    void CollisionComponent::init( leo::FrameType _frameType, leo::FrameInfo _frameInfo )
    {
        assert( !isValid() );
        assert( gSystems->containsSystem<CollisionSystem>() ); //You can't initialize a collision component if there is no collision system

        if (!gSystems->containsSystem<CollisionSystem>()) return; // Early return if the collision system does not exists

        auto collisionSystem = gSystems->getSystem<CollisionSystem>();

        leo::IWorld* world = gPhysics->getWorld( collisionSystem->getWorldId() );

        leo::FrameID frameId;

        switch (_frameType)
        {
        case leo::FrameType::Dynamic:    frameId = world->addDynamicFrame( _frameInfo ); break;
        case leo::FrameType::Static:     frameId = world->addStaticFrame( _frameInfo ); break;
        case leo::FrameType::Kinematic:  frameId = world->addKinematicFrame( _frameInfo ); break;
        default: assert( false ); break;
        }

        m_frameType = _frameType;
        m_frameId = frameId;
    }

    void CollisionComponent::uninit()
    { 
        assert( isValid() );
        
        leo::IFrame* frame = gPhysics->getFrame( m_frameId );
        for ( const leo::FramePartID& framePartId : m_bodyIds )
        {
            frame->removeFramePart( framePartId );
        }

        for ( const leo::FramePartID framePartId : m_triggerIds )
        {
            frame->removeFramePart( framePartId );
        }

        m_bodyIds.clear();
        m_triggerIds.clear();

        m_frameId.invalidate(); 
        m_frameType = leo::FrameType::Invalid; 
    }
    
    void CollisionComponent::onEnabled()
    {
        leo::IFrame* frame = gPhysics->getFrame( m_frameId );
        frame->enable();
    }
    
    void CollisionComponent::onDisabled()
    {
        leo::IFrame* frame = gPhysics->getFrame( m_frameId );
        frame->disable();
    }

    const leo::IDynamicFrame* CollisionComponent::getDynamicFrame() const
    {
        assert( leo::FrameType::Dynamic == m_frameType );
        if ( leo::FrameType::Dynamic == m_frameType )
        {
            return gPhysics->getDynamicFrame( m_frameId );
        }
        return nullptr;
    }

    leo::IDynamicFrame* CollisionComponent::getDynamicFrame()
    {
        assert( leo::FrameType::Dynamic == m_frameType );
        if ( leo::FrameType::Dynamic == m_frameType )
        {
            return gPhysics->getDynamicFrame( m_frameId );
        }
        return nullptr;
    }

    const leo::IKinematicFrame* CollisionComponent::getKinematicFrame() const
    {
        assert( leo::FrameType::Kinematic == m_frameType );
        if ( leo::FrameType::Kinematic == m_frameType )
        {
            return gPhysics->getKinematicFrame( m_frameId );
        }
        return nullptr;
    }

    leo::IKinematicFrame* CollisionComponent::getKinematicFrame()
    {
        assert( leo::FrameType::Kinematic == m_frameType );
        if ( leo::FrameType::Kinematic == m_frameType )
        {
            return gPhysics->getKinematicFrame( m_frameId );
        }
        return nullptr;
    }

    const leo::IStaticFrame* CollisionComponent::getStaticFrame() const
    {
        assert( leo::FrameType::Static == m_frameType );
        if ( leo::FrameType::Static == m_frameType )
        {
            return gPhysics->getStaticFrame( m_frameId );
        }
        return nullptr;
    }
    leo::IStaticFrame* CollisionComponent::getStaticFrame()
    {
        assert( leo::FrameType::Static == m_frameType );
        if ( leo::FrameType::Static == m_frameType )
        {
            return gPhysics->getStaticFrame( m_frameId );
        }
        return nullptr;
    }

    leo::FramePartID CollisionComponent::addBody( const leo::BodyInfo& _bodyInfo )
    {
        assert( isValid() );

        leo::IFrame* frame = gPhysics->getFrame( m_frameId );
        leo::FramePartID result = frame->addBody( _bodyInfo );
        m_bodyIds.emplace_back( result );
        return result;
    }

    leo::FramePartID CollisionComponent::addTrigger( const leo::TriggerInfo& _triggerInfo )
    {
        assert( isValid() );

        leo::IFrame* frame = gPhysics->getFrame( m_frameId );
        leo::FramePartID result = frame->addTrigger( _triggerInfo );
        m_bodyIds.emplace_back( result );
        return result;
    }
}