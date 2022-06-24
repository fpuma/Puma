#include <precompiledengine.h>

#include "collisionindexes.h"

namespace test
{
    const puma::leo::CollisionIndex TestCollisionIndexes::Ball = puma::leo::CollisionIndex( 1 );
    const puma::leo::CollisionIndex TestCollisionIndexes::Floor = puma::leo::CollisionIndex( 2 );
    const puma::leo::CollisionIndex TestCollisionIndexes::BallSpawner = puma::leo::CollisionIndex( 3 );
}