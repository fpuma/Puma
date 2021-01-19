#pragma once

#include <physics/simulation/frames/frameinfo.h>
#include <physics/simulation/frameparts/bodyinfo.h>
#include <physics/simulation/frameparts/triggerinfo.h>
#include <physics/ids/ids.h>

namespace puma
{
    using PhysicsFrameInfo = physics::FrameInfo;
    using PhysicsBodyInfo = physics::BodyInfo;
    using PhysicsTriggerInfo = physics::TriggerInfo;

    using PhysicsCollisionIndex = physics::CollisionIndex;

    constexpr PhysicsCollisionIndex kPhysicsDefaultCollisionIndex = physics::kDefaultCollisionID;
    constexpr u32 kPhysicsMaxCollisionCategories = physics::kMaxCollisionCateogries;
    using PhysicsCollisionRelation = physics::CollisionRelation;
    using PhysicsCollisionCompatibility = physics::CollisionCompatibility;
    using PhyscisCollisionMask = physics::CollisionMask;
    using PhysicsUserCollisionData = physics::UserCollisionData;

    using PhysicsFrameType = physics::FrameType;
    using PhysicsFramePartType = physics::FramePartType;

    using PhysicsWorldID = physics::WorldID;
    using PhysicsFrameID = physics::FrameID;
    using PhysicsFramePartID = physics::FramePartID;

}