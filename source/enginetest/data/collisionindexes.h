#pragma once

#include <engine/physics/physicsdefinitions.h>

namespace test
{
    const struct TestCollisionIndexes
    {
        static const puma::LeoCollisionIndex Ball;
        static const puma::LeoCollisionIndex Floor;
        static const puma::LeoCollisionIndex BallSpawner;
    };

    static const puma::LeoCollisionCompatibility kCollisionCompatibility =
    {
        { TestCollisionIndexes::Ball, TestCollisionIndexes::Floor },
        { TestCollisionIndexes::BallSpawner, TestCollisionIndexes::Floor },
        { TestCollisionIndexes::Ball, TestCollisionIndexes::Ball },
    };
}