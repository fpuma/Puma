#include <precompiledengine.h>

#include "inputactions.h"

namespace test
{
    const puma::InputAction TestInputActions::SpawnBallAction = puma::InputAction( 0 );
    const puma::InputAction TestInputActions::MoveBallSpawner = puma::InputAction( 1 );
    const puma::InputAction TestInputActions::MoveBallSpawnerStartUp = puma::InputAction( 2 );
    const puma::InputAction TestInputActions::MoveBallSpawnerStartDown = puma::InputAction( 3 );
    const puma::InputAction TestInputActions::MoveBallSpawnerStartLeft = puma::InputAction( 4 );
    const puma::InputAction TestInputActions::MoveBallSpawnerStartRight = puma::InputAction( 5 );
    const puma::InputAction TestInputActions::MoveBallSpawnerStopUp = puma::InputAction( 6 );
    const puma::InputAction TestInputActions::MoveBallSpawnerStopDown = puma::InputAction( 7 );
    const puma::InputAction TestInputActions::MoveBallSpawnerStopLeft = puma::InputAction( 8 );
    const puma::InputAction TestInputActions::MoveBallSpawnerStopRight = puma::InputAction( 9 );
    
    const puma::InputAction TestInputActions::InvertGravity = puma::InputAction( 10 );
}