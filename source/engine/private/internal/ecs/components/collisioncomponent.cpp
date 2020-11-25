#include <precompiledengine.h>

#include <internal/ecs/components/collisioncomponent.h>
#include <internal/services/physicsservice.h>

#include <physics/simulation/frames/iframe.h>
#include <physics/simulation/world/iworld.h>

namespace puma
{

    void CollisionComponent::init( FrameType _frameType, FrameInfo _frameInfo/*, WorldID _worldId*/ )
    {
        assert( !isValid() );

        m_frameType = _frameType;

        IWorld* world = gPhysics->getDefaultWorld();

        switch ( m_frameType )
        {
        case FrameType::Dynamic:    m_frameId = world->addDynamicFrame( _frameInfo ); break;
        case FrameType::Static:     m_frameId = world->addStaticFrame( _frameInfo ); break;
        case FrameType::Kinematic:  m_frameId = world->addKinematicFrame( _frameInfo ); break;
        default: break;
        }
    }

    void CollisionComponent::addBody( BodyInfo _bodyInfo )
    {
        assert( isValid() );

        IFrame* frame = gPhysics->getFrame( m_frameId );
        m_bodyIds.emplace_back( frame->addBody( _bodyInfo ) );
    }

    void CollisionComponent::addTrigger( TriggerInfo _triggerInfo )
    {
        assert( isValid() );

        IFrame* frame = gPhysics->getFrame( m_frameId );
        m_bodyIds.emplace_back( frame->addTrigger( _triggerInfo ) );
    }
}