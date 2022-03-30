#pragma once

#include <engine/ecs/base/entity.h>
#include <engine/utils/position.h>

using namespace puma;

class ShipSpawner
{
public:

    static Entity spawnShip(Position _pos);
    static void unspawnShip( Entity _entity );

};