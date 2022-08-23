#pragma once

#include <modules/leo/leodefinitions.h>

namespace test
{
    const struct TestCollisionIndexes
    {
        static const puma::leo::CollisionIndex Ball;
        static const puma::leo::CollisionIndex Floor;
        static const puma::leo::CollisionIndex BallSpawner;
    };

    static const puma::leo::CollisionCompatibility kCollisionCompatibility =
    {
        { TestCollisionIndexes::Ball, TestCollisionIndexes::Floor },
        { TestCollisionIndexes::BallSpawner, TestCollisionIndexes::Floor },
        { TestCollisionIndexes::Ball, TestCollisionIndexes::Ball },
    };
}