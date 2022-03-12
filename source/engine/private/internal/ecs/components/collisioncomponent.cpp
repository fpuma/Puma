#include <precompiledengine.h>

#include <internal/ecs/components/collisioncomponent.h>
#include <internal/services/physicsservice.h>

#include <physics/simulation/frames/iframe.h>
#include <physics/simulation/world/iworld.h>

namespace puma
{

    void CollisionComponent::init( PhysicsFrameType _frameType, PhysicsFrameID _frameId )
    {
        assert( !isValid() );

        m_frameType = _frameType;
        m_frameId = _frameId;
    }

    void CollisionComponent::uninit()
    { 
        physics::IFrame* frame = gPhysics->getFrame( m_frameId );
        for ( const PhysicsFramePartID& framePartId : m_bodyIds )
        {
            frame->removeFramePart( framePartId );
        }

        for ( const PhysicsFramePartID framePartId : m_triggerIds )
        {
            frame->removeFramePart( framePartId );
        }

        m_bodyIds.clear();
        m_triggerIds.clear();

        m_frameId.invalidate(); 
        m_frameType = PhysicsFrameType::Invalid; 
    }
    
    const PhysicsDynamicFrame* CollisionComponent::getDynamicFrame() const
    {
        assert( PhysicsFrameType::Dynamic == m_frameType );
        if ( PhysicsFrameType::Dynamic == m_frameType )
        {
            return gPhysics->getDynamicFrame( m_frameId );
        }
        return nullptr;
    }

    PhysicsDynamicFrame* CollisionComponent::getDynamicFrame()
    {
        assert( PhysicsFrameType::Dynamic == m_frameType );
        if ( PhysicsFrameType::Dynamic == m_frameType )
        {
            return gPhysics->getDynamicFrame( m_frameId );
        }
        return nullptr;
    }

    const PhysicsKinematicFrame* CollisionComponent::getKinematicFrame() const
    {
        assert( PhysicsFrameType::Kinematic == m_frameType );
        if ( PhysicsFrameType::Kinematic == m_frameType )
        {
            return gPhysics->getKinematicFrame( m_frameId );
        }
        return nullptr;
    }

    PhysicsKinematicFrame* CollisionComponent::getKinematicFrame()
    {
        assert( PhysicsFrameType::Static == m_frameType );
        assert( PhysicsFrameType::Kinematic == m_frameType );
        if ( PhysicsFrameType::Kinematic == m_frameType )
        {
            return gPhysics->getKinematicFrame( m_frameId );
        }
        return nullptr;
    }

    const PhysicsStaticFrame* CollisionComponent::getStaticFrame() const
    {
        assert( PhysicsFrameType::Static == m_frameType );
        if ( PhysicsFrameType::Static == m_frameType )
        {
            return gPhysics->getStaticFrame( m_frameId );
        }
        return nullptr;
    }
    PhysicsStaticFrame* CollisionComponent::getStaticFrame()
    {
        assert( PhysicsFrameType::Static == m_frameType );
        if ( PhysicsFrameType::Static == m_frameType )
        {
            return gPhysics->getStaticFrame( m_frameId );
        }
        return nullptr;
    }

    void CollisionComponent::addBody( const PhysicsBodyInfo& _bodyInfo )
    {
        assert( isValid() );

        physics::IFrame* frame = gPhysics->getFrame( m_frameId );
        m_bodyIds.emplace_back( frame->addBody( _bodyInfo ) );
    }

    void CollisionComponent::addTrigger( const PhysicsTriggerInfo& _triggerInfo )
    {
        assert( isValid() );

        physics::IFrame* frame = gPhysics->getFrame( m_frameId );
        m_bodyIds.emplace_back( frame->addTrigger( _triggerInfo ) );
    }
}