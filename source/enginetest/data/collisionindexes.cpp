#include <precompiledengine.h>

#include "collisionindexes.h"

namespace test
{
    const puma::PhysicsCollisionIndex TestCollisionIndexes::Ball = puma::PhysicsCollisionIndex( 1 );
    const puma::PhysicsCollisionIndex TestCollisionIndexes::Floor = puma::PhysicsCollisionIndex( 2 );
    const puma::PhysicsCollisionIndex TestCollisionIndexes::BallSpawner = puma::PhysicsCollisionIndex( 3 );
}