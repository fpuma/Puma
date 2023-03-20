#pragma once

#include <modules/leo/leodefinitions.h>

namespace puma
{
    class IRenderQueue;
    namespace pina
    {
        class EntityProvider;
        class ComponentProvider;
    }

    class System
    {
    public:

        virtual ~System() {}

        virtual void onInit() = 0;
        virtual void onUninit() = 0;

        void enable() { m_enabled = true; }
        void disable() { m_enabled = false; }
        bool isEnabled() const { return m_enabled; }

        virtual void update( pina::EntityProvider& _entityProvider, pina::ComponentProvider& _componentProvider ) { assert( false ); /*Trying to call update on a system that has not implemented it*/ };
        virtual void prePhysicsUpdate( pina::EntityProvider& _entityProvider, pina::ComponentProvider& _componentProvider ) { assert( false ); /*Trying to call prePhysicsUpdate on a system that has not implemented it*/ };
        virtual void postPhysicsUpdate( pina::EntityProvider& _entityProvider, pina::ComponentProvider& _componentProvider ) { assert( false ); /*Trying to call postPhysicsUpdate on a system that has not implemented it*/ };

        virtual void queueRenderables( IRenderQueue& _renderQueue ) { assert( false ); /*Trying to call queueRenderables on a system that has not implemented it*/ };

        // If any of the frame parts is a trigger, the contact point will be invalid
        virtual void onCollisionStarted( leo::FramePartID _framePartPtrA, leo::FramePartID _framePartPtrB, leo::ContactPoint _contactPoint ) { assert( false ); /*Trying to call onCollisionDetected on a system that has not implemented it*/ }
        virtual void onCollisionStopped( leo::FramePartID _framePartPtrA, leo::FramePartID _framePartPtrB ) { assert( false ); /*Trying to call onCollisionDetected on a system that has not implemented it*/ }

    private:

        bool m_enabled = true;
    };

}