#include <precompiledengine.h>

#include <internal/ecs/components/collisioncomponent.h>
#include <internal/services/physicsservice.h>

#include <physics/simulation/frames/iframe.h>
#include <physics/simulation/world/iworld.h>

namespace puma
{

    void CollisionComponent::init( physics::FrameType _frameType, physics::FrameID _frameId )
    {
        assert( !isValid() );

        m_frameType = _frameType;
        m_frameId = _frameId;
    }

    void CollisionComponent::uninit()
    { 
        physics::IFrame* frame = gPhysics->getFrame( m_frameId );
        for ( const physics::FramePartID& framePartId : m_bodyIds )
        {
            frame->removeFramePart( framePartId );
        }

        for ( const physics::FramePartID framePartId : m_triggerIds )
        {
            frame->removeFramePart( framePartId );
        }

        m_frameId = physics::kInvalidPhysicsID; 
        m_frameType = physics::FrameType::Invalid; 
    }

    void CollisionComponent::addBody( physics::BodyInfo _bodyInfo )
    {
        assert( isValid() );

        physics::IFrame* frame = gPhysics->getFrame( m_frameId );
        m_bodyIds.emplace_back( frame->addBody( _bodyInfo ) );
    }

    void CollisionComponent::addTrigger( physics::TriggerInfo _triggerInfo )
    {
        assert( isValid() );

        physics::IFrame* frame = gPhysics->getFrame( m_frameId );
        m_bodyIds.emplace_back( frame->addTrigger( _triggerInfo ) );
    }
}