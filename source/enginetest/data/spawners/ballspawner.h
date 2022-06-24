#pragma once

#include <engine/ecs/base/entity.h>
#include <engine/external/ninadefinitions.h>
#include <engine/utils/position.h>

namespace test
{
    puma::Entity spawnBall( puma::NinaTextureManager* _textureManager, const puma::Position& _pos );
    void unspawnBall( puma::Entity _ballEntity );
}