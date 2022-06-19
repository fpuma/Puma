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
        {TestInputActions::SpawnBallAction,             {puma::NinaKeyboardKey::KB_LCTRL, puma::InputModifier_NONE, puma::InputState::Pressed}},
        {TestInputActions::MoveBallSpawnerStartUp,      {puma::NinaKeyboardKey::KB_W, puma::InputModifier_NONE, puma::InputState::Pressed}},
        {TestInputActions::MoveBallSpawnerStartDown,    {puma::NinaKeyboardKey::KB_S, puma::InputModifier_NONE, puma::InputState::Pressed}},
        {TestInputActions::MoveBallSpawnerStartLeft,    {puma::NinaKeyboardKey::KB_A, puma::InputModifier_NONE, puma::InputState::Pressed}},
        {TestInputActions::MoveBallSpawnerStartRight,   {puma::NinaKeyboardKey::KB_D, puma::InputModifier_NONE, puma::InputState::Pressed}},
        {TestInputActions::MoveBallSpawnerStopUp,       {puma::NinaKeyboardKey::KB_W, puma::InputModifier_NONE, puma::InputState::Released}},
        {TestInputActions::MoveBallSpawnerStopDown,     {puma::NinaKeyboardKey::KB_S, puma::InputModifier_NONE, puma::InputState::Released}},
        {TestInputActions::MoveBallSpawnerStopLeft,     {puma::NinaKeyboardKey::KB_A, puma::InputModifier_NONE, puma::InputState::Released}},
        {TestInputActions::MoveBallSpawnerStopRight,    {puma::NinaKeyboardKey::KB_D, puma::InputModifier_NONE, puma::InputState::Released}},
    };

    static const InputActionKeyboardPairList kSpawner1KeyboardInput =
    {
        {TestInputActions::SpawnBallAction,             {puma::NinaKeyboardKey::KB_RCTRL,    puma::InputModifier_NONE, puma::InputState::Pressed}},
        {TestInputActions::MoveBallSpawnerStartUp,      {puma::NinaKeyboardKey::KB_UP,       puma::InputModifier_NONE, puma::InputState::Pressed}},
        {TestInputActions::MoveBallSpawnerStartDown,    {puma::NinaKeyboardKey::KB_DOWN,     puma::InputModifier_NONE, puma::InputState::Pressed}},
        {TestInputActions::MoveBallSpawnerStartLeft,    {puma::NinaKeyboardKey::KB_LEFT,     puma::InputModifier_NONE, puma::InputState::Pressed}},
        {TestInputActions::MoveBallSpawnerStartRight,   {puma::NinaKeyboardKey::KB_RIGHT,    puma::InputModifier_NONE, puma::InputState::Pressed}},
        {TestInputActions::MoveBallSpawnerStopUp,       {puma::NinaKeyboardKey::KB_UP,       puma::InputModifier_NONE, puma::InputState::Released}},
        {TestInputActions::MoveBallSpawnerStopDown,     {puma::NinaKeyboardKey::KB_DOWN,     puma::InputModifier_NONE, puma::InputState::Released}},
        {TestInputActions::MoveBallSpawnerStopLeft,     {puma::NinaKeyboardKey::KB_LEFT,     puma::InputModifier_NONE, puma::InputState::Released}},
        {TestInputActions::MoveBallSpawnerStopRight,    {puma::NinaKeyboardKey::KB_RIGHT,    puma::InputModifier_NONE, puma::InputState::Released}},
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
        {TestInputActions::SpawnBallAction,             {puma::NinaControllerButton::CB_LB, 0, puma::InputState::Pressed}},
    };

    static const InputActionControllerButtonPairList kSpawner1ControllerButtonInput =
    {
        {TestInputActions::SpawnBallAction,             {puma::NinaControllerButton::CB_RB, 0, puma::InputState::Pressed}},
    };
}