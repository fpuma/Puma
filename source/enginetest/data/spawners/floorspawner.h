#pragma once

#include <modules/pina/entity.h>
#include <modules/nina/ninadefinitions.h>
#include <engine/utils/position.h>

namespace test
{
    puma::Entity spawnFloor( puma::nina::ITextureManager* _textureManager, const puma::Position& _pos, float _angle );
    void unspawnFloor( puma::Entity _floorEntity );
}