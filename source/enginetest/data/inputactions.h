#pragma once

#include <engine/input/inputdefinitions.h>

namespace test
{
    const struct TestInputActions
    {
        static const puma::InputAction SpawnBallAction;
        static const puma::InputAction MoveBallSpawner;
        static const puma::InputAction MoveBallSpawnerUp;
        static const puma::InputAction MoveBallSpawnerDown;
        static const puma::InputAction MoveBallSpawnerLeft;
        static const puma::InputAction MoveBallSpawnerRight;
    }; 
}