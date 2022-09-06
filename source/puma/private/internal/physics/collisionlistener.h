#pragma once

#include <modules/leo/leodefinitions.h>

namespace puma
{
    class CollisionListener : public leo::ICollisionListener
    {
    public:

        void collisionStarted( leo::FramePartID _framePartA, leo::FramePartID _framePartB, leo::ContactPoint _contactPoint ) override;
        void collisionStopped( leo::FramePartID _framePartA, leo::FramePartID _framePartB ) override;

    };
}