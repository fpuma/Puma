#pragma once

#include <engine/ecs/base/entity.h>

using namespace puma;

class Asteroids
{
public:

    void init();
    void uninit();
    void update();

private:

    void initCamera();
    void uninitCamera();
    void initPhysics();

    Entity m_cameraEntity;
    Entity m_shipEntity;
};