#pragma once

#include <engine/input/inputdefinitions.h>

namespace test
{
    const struct TestInputActions
    {
        static const puma::InputAction SpawnBallAction;
        static const puma::InputAction MoveBallSpawner;
        static const puma::InputAction MoveBallSpawnerStartUp;
        static const puma::InputAction MoveBallSpawnerStartDown;
        static const puma::InputAction MoveBallSpawnerStartLeft;
        static const puma::InputAction MoveBallSpawnerStartRight;
        static const puma::InputAction MoveBallSpawnerStopUp;
        static const puma::InputAction MoveBallSpawnerStopDown;
        static const puma::InputAction MoveBallSpawnerStopLeft;
        static const puma::InputAction MoveBallSpawnerStopRight;

        static const puma::InputAction InvertGravity;

        static const puma::InputAction ToggleFloorEntity;
        static const puma::InputAction ToggleFloorPhysics;

        static const puma::InputAction MouseMove;
    }; 
}