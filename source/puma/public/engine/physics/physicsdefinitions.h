#pragma once

#include <physics/simulation/frameparts/bodyinfo.h>
#include <physics/simulation/frameparts/iframebody.h>
#include <physics/simulation/frameparts/iframetrigger.h>
#include <physics/simulation/frameparts/triggerinfo.h>
#include <physics/simulation/frames/frameinfo.h>
#include <physics/simulation/frames/idynamicframe.h>
#include <physics/simulation/frames/ikinematicframe.h>
#include <physics/simulation/frames/istaticframe.h>
#include <physics/ids/ids.h>

namespace puma
{
    using LeoFrameInfo = leo::FrameInfo;
    using LeoBodyInfo = leo::BodyInfo;
    using LeoTriggerInfo = leo::TriggerInfo;

    using LeoDynamicFrame = leo::IDynamicFrame;
    using LeoKinematicFrame = leo::IKinematicFrame;
    using LeoStaticFrame = leo::IStaticFrame;

    using LeoBodyPart = leo::IFrameBody;
    using LeoTriggerPart = leo::IFrameTrigger;

    using LeoCollisionIndex = leo::CollisionIndex;

    constexpr LeoCollisionIndex kLeoDefaultCollisionIndex = leo::kDefaultCollisionID;
    constexpr u32 kLeoMaxCollisionCategories = leo::kMaxCollisionCateogries;
    using LeoCollisionRelation = leo::CollisionRelation;
    using LeoCollisionCompatibility = leo::CollisionCompatibility;
    using LeoCollisionMask = leo::CollisionMask;
    using LeoUserCollisionData = leo::UserCollisionData;

    using LeoFrameType = leo::FrameType;
    using LeoFramePartType = leo::FramePartType;

    using LeoWorldID = leo::WorldID;
    using LeoFrameID = leo::FrameID;
    using LeoFramePartID = leo::FramePartID;

}