#pragma once

#include <engine/ecs/base/entity.h>
#include <engine/input/inputdefinitions.h>
#include <data/inputactions.h>
#include <engine/utils/position.h>

namespace test
{
    using InputActionKeyboardPairList = std::initializer_list<std::pair<puma::InputAction, puma::KeyboardInput>>;
    using InputActionControllerPairList = std::initializer_list<std::pair<puma::InputAction, puma::ControllerJoystickInput>>;
    using InputActionControllerButtonPairList = std::initializer_list<std::pair<puma::InputAction, puma::ControllerButtonInput>>;

    puma::Entity spawnBallSpawner(  const InputActionKeyboardPairList& _keyboardInputList, 
                                    const InputActionControllerPairList& _controllerInputList, 
                                    const InputActionControllerButtonPairList& _controllerButtonInputList,
                                    const puma::Position& _position );
    void unspawnBallSpawner( puma::Entity _spawnerEntity );

    static const InputActionKeyboardPairList kSpawner0KeyboardInput =
    {
        {TestInputActions::SpawnBallAction,             {puma::AppKeyboardKey::KB_LCTRL, puma::InputModifier::NONE, puma::InputState::Pressed}},
        {TestInputActions::MoveBallSpawnerStartUp,      {puma::AppKeyboardKey::KB_W, puma::InputModifier::NONE, puma::InputState::Pressed}},
        {TestInputActions::MoveBallSpawnerStartDown,    {puma::AppKeyboardKey::KB_S, puma::InputModifier::NONE, puma::InputState::Pressed}},
        {TestInputActions::MoveBallSpawnerStartLeft,    {puma::AppKeyboardKey::KB_A, puma::InputModifier::NONE, puma::InputState::Pressed}},
        {TestInputActions::MoveBallSpawnerStartRight,   {puma::AppKeyboardKey::KB_D, puma::InputModifier::NONE, puma::InputState::Pressed}},
        {TestInputActions::MoveBallSpawnerStopUp,       {puma::AppKeyboardKey::KB_W, puma::InputModifier::NONE, puma::InputState::Released}},
        {TestInputActions::MoveBallSpawnerStopDown,     {puma::AppKeyboardKey::KB_S, puma::InputModifier::NONE, puma::InputState::Released}},
        {TestInputActions::MoveBallSpawnerStopLeft,     {puma::AppKeyboardKey::KB_A, puma::InputModifier::NONE, puma::InputState::Released}},
        {TestInputActions::MoveBallSpawnerStopRight,    {puma::AppKeyboardKey::KB_D, puma::InputModifier::NONE, puma::InputState::Released}},
    };

    static const InputActionKeyboardPairList kSpawner1KeyboardInput =
    {
        {TestInputActions::SpawnBallAction,             {puma::AppKeyboardKey::KB_RCTRL,    puma::InputModifier::NONE, puma::InputState::Pressed}},
        {TestInputActions::MoveBallSpawnerStartUp,      {puma::AppKeyboardKey::KB_UP,       puma::InputModifier::NONE, puma::InputState::Pressed}},
        {TestInputActions::MoveBallSpawnerStartDown,    {puma::AppKeyboardKey::KB_DOWN,     puma::InputModifier::NONE, puma::InputState::Pressed}},
        {TestInputActions::MoveBallSpawnerStartLeft,    {puma::AppKeyboardKey::KB_LEFT,     puma::InputModifier::NONE, puma::InputState::Pressed}},
        {TestInputActions::MoveBallSpawnerStartRight,   {puma::AppKeyboardKey::KB_RIGHT,    puma::InputModifier::NONE, puma::InputState::Pressed}},
        {TestInputActions::MoveBallSpawnerStopUp,       {puma::AppKeyboardKey::KB_UP,       puma::InputModifier::NONE, puma::InputState::Released}},
        {TestInputActions::MoveBallSpawnerStopDown,     {puma::AppKeyboardKey::KB_DOWN,     puma::InputModifier::NONE, puma::InputState::Released}},
        {TestInputActions::MoveBallSpawnerStopLeft,     {puma::AppKeyboardKey::KB_LEFT,     puma::InputModifier::NONE, puma::InputState::Released}},
        {TestInputActions::MoveBallSpawnerStopRight,    {puma::AppKeyboardKey::KB_RIGHT,    puma::InputModifier::NONE, puma::InputState::Released}},
    };

    static const InputActionControllerPairList kSpawner0ControllerJoystickInput =
    {
        {TestInputActions::MoveBallSpawner,             {puma::ControllerJoystick::LEFT_STICK, 0}},
    };

    static const InputActionControllerPairList kSpawner1ControllerJoystickInput =
    {
        {TestInputActions::MoveBallSpawner,             {puma::ControllerJoystick::RIGHT_STICK, 0}},
    };

    static const InputActionControllerButtonPairList kSpawner0ControllerButtonInput =
    {
        {TestInputActions::SpawnBallAction,             {puma::AppControllerButton::CB_LB, 0, puma::InputState::Pressed}},
    };

    static const InputActionControllerButtonPairList kSpawner1ControllerButtonInput =
    {
        {TestInputActions::SpawnBallAction,             {puma::AppControllerButton::CB_RB, 0, puma::InputState::Pressed}},
    };
}