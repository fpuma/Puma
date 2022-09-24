#include <precompiledengine.h>

#include <internal/ecs/components/collisioncomponent.h>
#include <internal/services/physicsservice.h>

#include <leo/simulation/frames/iframe.h>
#include <leo/simulation/world/iworld.h>

namespace puma
{

    void CollisionComponent::init( leo::FrameType _frameType, leo::FrameID _frameId )
    {
        assert( !isValid() );

        m_frameType = _frameType;
        m_frameId = _frameId;
    }

    void CollisionComponent::uninit()
    { 
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