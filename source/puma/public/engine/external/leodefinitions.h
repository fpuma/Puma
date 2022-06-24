#pragma once

#include <leo/simulation/frameparts/bodyinfo.h>
#include <leo/simulation/frameparts/iframebody.h>
#include <leo/simulation/frameparts/iframetrigger.h>
#include <leo/simulation/frameparts/triggerinfo.h>
#include <leo/simulation/frames/frameinfo.h>
#include <leo/simulation/frames/idynamicframe.h>
#include <leo/simulation/frames/ikinematicframe.h>
#include <leo/simulation/frames/istaticframe.h>
#include <leo/ids/ids.h>

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