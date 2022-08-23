#pragma once

#include <engine/ecs/base/entity.h>
#include <modules/nina/ninadefinitions.h>
#include <engine/utils/position.h>

namespace test
{
    puma::Entity spawnBall( puma::nina::ITextureManager* _textureManager, const puma::Position& _pos );
    void unspawnBall( puma::Entity _ballEntity );
}