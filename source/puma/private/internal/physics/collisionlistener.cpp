#include <precompiledengine.h>

#include <internal/physics/collisionlistener.h>
#include <engine/services/ecsservice.h>
#include <engine/services/systemsservice.h>

namespace puma
{
    void CollisionListener::collisionStarted( leo::FramePartID _framePartA, leo::FramePartID _framePartB, leo::ContactPoint _contactPoint )
    {
        gSystems->onCollisionStarted( _framePartA, _framePartB, _contactPoint );
    }

    void CollisionListener::collisionStopped( leo::FramePartID _framePartA, leo::FramePartID _framePartB )
    {
        gSystems->onCollisionStopped( _framePartA, _framePartB );
    }
}