#pragma once

#include <engine/ecs/base/entity.h>
#include <application/commondefinitions.h>


namespace puma::app
{
    class ITextureManager;
}


puma::Entity spawnFloor( puma::app::WindowHandle _windowHandle, puma::app::ITextureManager* _textureManager );
void unspawnFloor( puma::Entity _floorEntity );

puma::Entity spawnBall( puma::app::WindowHandle _windowHandle, puma::app::ITextureManager* _textureManager );
void unspawnBall( puma::Entity _floorEntity );

void initPhysics();