#pragma once

#include <engine/ecs/base/entity.h>
#include <engine/application/applicationdefinitions.h>
#include <engine/utils/position.h>

namespace test
{
    puma::Entity spawnBackground( puma::NinaTextureManager* _textureManager, const puma::Position& _pos );
    void unspawnBackground( puma::Entity _ballEntity );
}