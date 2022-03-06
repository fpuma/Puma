#include <precompiledengine.h>

#include "inputactions.h"

namespace test
{
    const puma::InputAction TestInputActions::SpawnBallAction = puma::InputAction( 0 );
    const puma::InputAction TestInputActions::MoveBallSpawner = puma::InputAction( 1 );
    const puma::InputAction TestInputActions::MoveBallSpawnerUp = puma::InputAction( 2 );
    const puma::InputAction TestInputActions::MoveBallSpawnerDown = puma::InputAction( 3 );
    const puma::InputAction TestInputActions::MoveBallSpawnerLeft = puma::InputAction( 4 );
    const puma::InputAction TestInputActions::MoveBallSpawnerRight = puma::InputAction( 5 );
}