#pragma once

#include <engine/ecs/base/entity.h>
#include <engine/input/inputdefinitions.h>
#include <data/inputactions.h>
#include <engine/utils/position.h>

namespace test
{
    using InputActionKeyboardPairList = std::initializer_list<std::pair<puma::InputAction, puma::KeyboardInput>>;

    puma::Entity spawnBallSpawner( InputActionKeyboardPairList _keyboardInputList, const puma::Position& _position );
    void unspawnBallSpawner( puma::Entity _spawnerEntity );

    static const InputActionKeyboardPairList kSpawner0KeyboardInput =
    {
        {TestInputActions::SpawnBallAction,         {puma::AppKeyboardKey::KB_LCTRL, puma::InputModifier::NONE, puma::InputState::Pressed}},
        {TestInputActions::MoveBallSpawnerUp,       {puma::AppKeyboardKey::KB_W, puma::InputModifier::NONE, puma::InputState::Pressed}},
        {TestInputActions::MoveBallSpawnerDown,     {puma::AppKeyboardKey::KB_S, puma::InputModifier::NONE, puma::InputState::Pressed}},
        {TestInputActions::MoveBallSpawnerLeft,     {puma::AppKeyboardKey::KB_A, puma::InputModifier::NONE, puma::InputState::Pressed}},
        {TestInputActions::MoveBallSpawnerRight,    {puma::AppKeyboardKey::KB_D, puma::InputModifier::NONE, puma::InputState::Pressed}},
    };

    static const InputActionKeyboardPairList kSpawner1KeyboardInput =
    {
        {TestInputActions::SpawnBallAction,         {puma::AppKeyboardKey::KB_RCTRL, puma::InputModifier::NONE, puma::InputState::Pressed}},
        {TestInputActions::MoveBallSpawnerUp,       {puma::AppKeyboardKey::KB_UP, puma::InputModifier::NONE, puma::InputState::Pressed}},
        {TestInputActions::MoveBallSpawnerDown,     {puma::AppKeyboardKey::KB_DOWN, puma::InputModifier::NONE, puma::InputState::Pressed}},
        {TestInputActions::MoveBallSpawnerLeft,     {puma::AppKeyboardKey::KB_LEFT, puma::InputModifier::NONE, puma::InputState::Pressed}},
        {TestInputActions::MoveBallSpawnerRight,    {puma::AppKeyboardKey::KB_RIGHT, puma::InputModifier::NONE, puma::InputState::Pressed}},
    };
}