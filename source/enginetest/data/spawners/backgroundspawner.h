#pragma once

#include <pina/entity.h>
#include <modules/nina/ninadefinitions.h>
#include <engine/utils/position.h>

namespace test
{
    puma::pina::Entity spawnBackground( puma::nina::ITextureManager* _textureManager, const puma::Position& _pos );
    void unspawnBackground( puma::pina::Entity _ballEntity );
}