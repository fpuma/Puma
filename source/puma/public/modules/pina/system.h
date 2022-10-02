#pragma once

#include <pina/system.h>
#include <modules/leo/leodefinitions.h>

namespace puma
{
    class IRenderQueue;
    class EntityProvider;
    class ComponentProvider;
    
    class System : public pina::System
    {
    public:

        virtual ~System() {}

        virtual void update( EntityProvider& _entityProvider, ComponentProvider& _componentProvider ) { assert( false ); /*Trying to call update on a system that has not implemented it*/ };
        virtual void prePhysicsUpdate( EntityProvider& _entityProvider, ComponentProvider& _componentProvider ) { assert( false ); /*Trying to call prePhysicsUpdate on a system that has not implemented it*/ };
        virtual void postPhysicsUpdate( EntityProvider& _entityProvider, ComponentProvider& _componentProvider ) { assert( false ); /*Trying to call postPhysicsUpdate on a system that has not implemented it*/ };

        virtual void queueRenderables( IRenderQueue& _renderQueue ) { assert( false ); /*Trying to call queueRenderables on a system that has not implemented it*/ };

        // If any of the frame parts is a trigger, the contact point will be invalid
        virtual void onCollisionStarted( leo::FramePartID _framePartPtrA, leo::FramePartID _framePartPtrB, leo::ContactPoint _contactPoint ) { assert( false ); /*Trying to call onCollisionDetected on a system that has not implemented it*/ }
        virtual void onCollisionStopped( leo::FramePartID _framePartPtrA, leo::FramePartID _framePartPtrB ) { assert( false ); /*Trying to call onCollisionDetected on a system that has not implemented it*/ }
    };

}