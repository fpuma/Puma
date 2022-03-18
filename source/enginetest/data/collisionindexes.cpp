#include <precompiledengine.h>

#include "collisionindexes.h"

namespace test
{
    const puma::LeoCollisionIndex TestCollisionIndexes::Ball = puma::LeoCollisionIndex( 1 );
    const puma::LeoCollisionIndex TestCollisionIndexes::Floor = puma::LeoCollisionIndex( 2 );
    const puma::LeoCollisionIndex TestCollisionIndexes::BallSpawner = puma::LeoCollisionIndex( 3 );
}