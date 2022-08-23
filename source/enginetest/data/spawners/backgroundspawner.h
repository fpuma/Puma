#pragma once

#include <modules/pina/entity.h>
#include <modules/nina/ninadefinitions.h>
#include <engine/utils/position.h>

namespace test
{
    puma::Entity spawnBackground( puma::nina::ITextureManager* _textureManager, const puma::Position& _pos );
    void unspawnBackground( puma::Entity _ballEntity );
}