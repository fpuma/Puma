#pragma once

#include <engine/physics/physicsdefinitions.h>

namespace test
{
    const struct TestCollisionIndexes
    {
        static const puma::PhysicsCollisionIndex Ball;
        static const puma::PhysicsCollisionIndex Floor;
        static const puma::PhysicsCollisionIndex BallSpawner;
    };

    static const puma::PhysicsCollisionCompatibility kCollisionCompatibility =
    {
        { TestCollisionIndexes::Ball, TestCollisionIndexes::Floor },
        { TestCollisionIndexes::BallSpawner, TestCollisionIndexes::Floor },
        { TestCollisionIndexes::Ball, TestCollisionIndexes::Ball },
    };
}