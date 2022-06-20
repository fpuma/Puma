#include <precompiledengine.h>

#include <internal/ecs/components/collisioncomponent.h>
#include <internal/services/physicsservice.h>

#include <leo/simulation/frames/iframe.h>
#include <leo/simulation/world/iworld.h>

namespace puma
{

    void CollisionComponent::init( LeoFrameType _frameType, LeoFrameID _frameId )
    {
        assert( !isValid() );

        m_frameType = _frameType;
        m_frameId = _frameId;
    }

    void CollisionComponent::uninit()
    { 
        leo::IFrame* frame = gPhysics->getFrame( m_frameId );
        for ( const LeoFramePartID& framePartId : m_bodyIds )
        {
            frame->removeFramePart( framePartId );
        }

        for ( const LeoFramePartID framePartId : m_triggerIds )
        {
            frame->removeFramePart( framePartId );
        }

        m_bodyIds.clear();
        m_triggerIds.clear();

        m_frameId.invalidate(); 
        m_frameType = LeoFrameType::Invalid; 
    }
    
    const LeoDynamicFrame* CollisionComponent::getDynamicFrame() const
    {
        assert( LeoFrameType::Dynamic == m_frameType );
        if ( LeoFrameType::Dynamic == m_frameType )
        {
            return gPhysics->getDynamicFrame( m_frameId );
        }
        return nullptr;
    }

    LeoDynamicFrame* CollisionComponent::getDynamicFrame()
    {
        assert( LeoFrameType::Dynamic == m_frameType );
        if ( LeoFrameType::Dynamic == m_frameType )
        {
            return gPhysics->getDynamicFrame( m_frameId );
        }
        return nullptr;
    }

    const LeoKinematicFrame* CollisionComponent::getKinematicFrame() const
    {
        assert( LeoFrameType::Kinematic == m_frameType );
        if ( LeoFrameType::Kinematic == m_frameType )
        {
            return gPhysics->getKinematicFrame( m_frameId );
        }
        return nullptr;
    }

    LeoKinematicFrame* CollisionComponent::getKinematicFrame()
    {
        assert( LeoFrameType::Static == m_frameType );
        assert( LeoFrameType::Kinematic == m_frameType );
        if ( LeoFrameType::Kinematic == m_frameType )
        {
            return gPhysics->getKinematicFrame( m_frameId );
        }
        return nullptr;
    }

    const LeoStaticFrame* CollisionComponent::getStaticFrame() const
    {
        assert( LeoFrameType::Static == m_frameType );
        if ( LeoFrameType::Static == m_frameType )
        {
            return gPhysics->getStaticFrame( m_frameId );
        }
        return nullptr;
    }
    LeoStaticFrame* CollisionComponent::getStaticFrame()
    {
        assert( LeoFrameType::Static == m_frameType );
        if ( LeoFrameType::Static == m_frameType )
        {
            return gPhysics->getStaticFrame( m_frameId );
        }
        return nullptr;
    }

    void CollisionComponent::addBody( const LeoBodyInfo& _bodyInfo )
    {
        assert( isValid() );

        leo::IFrame* frame = gPhysics->getFrame( m_frameId );
        m_bodyIds.emplace_back( frame->addBody( _bodyInfo ) );
    }

    void CollisionComponent::addTrigger( const LeoTriggerInfo& _triggerInfo )
    {
        assert( isValid() );

        leo::IFrame* frame = gPhysics->getFrame( m_frameId );
        m_bodyIds.emplace_back( frame->addTrigger( _triggerInfo ) );
    }
}