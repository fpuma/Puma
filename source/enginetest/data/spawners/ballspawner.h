#pragma once

#include <engine/ecs/base/entity.h>
#include <engine/application/applicationdefinitions.h>
#include <engine/utils/position.h>

namespace test
{
    puma::Entity spawnBall( puma::AppTextureManager* _textureManager, const puma::Position& _pos );
    void unspawnBall( puma::Entity _ballEntity );
}