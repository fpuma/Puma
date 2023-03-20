#pragma once

#include <pina/entity.h>
#include <engine/input/inputdefinitions.h>
#include <data/inputactions.h>
#include <engine/utils/position.h>

namespace test
{
    using InputActionKeyboardPairList = std::initializer_list<std::pair<puma::InputAction, puma::KeyboardInput>>;
    using InputActionControllerPairList = std::initializer_list<std::pair<puma::InputAction, puma::ControllerJoystickInput>>;
    using InputActionControllerButtonPairList = std::initializer_list<std::pair<puma::InputAction, puma::ControllerButtonInput>>;

    puma::pina::Entity spawnBallSpawner(  const InputActionKeyboardPairList& _keyboardInputList,
                                    const InputActionControllerPairList& _controllerInputList, 
                                    const InputActionControllerButtonPairList& _controllerButtonInputList,
                                    const puma::Position& _position );
    void unspawnBallSpawner( puma::pina::Entity _spawnerEntity );

    static const InputActionKeyboardPairList kSpawner0KeyboardInput =
    {
        {TestInputActions::SpawnBallAction,             {puma::nina::KeyboardKey::KB_LCTRL, puma::InputModifier_NONE, puma::nina::InputButtonEvent::Pressed}},
        {TestInputActions::MoveBallSpawnerStartUp,      {puma::nina::KeyboardKey::KB_W, puma::InputModifier_NONE, puma::nina::InputButtonEvent::Pressed}},
        {TestInputActions::MoveBallSpawnerStartDown,    {puma::nina::KeyboardKey::KB_S, puma::InputModifier_NONE, puma::nina::InputButtonEvent::Pressed}},
        {TestInputActions::MoveBallSpawnerStartLeft,    {puma::nina::KeyboardKey::KB_A, puma::InputModifier_NONE, puma::nina::InputButtonEvent::Pressed}},
        {TestInputActions::MoveBallSpawnerStartRight,   {puma::nina::KeyboardKey::KB_D, puma::InputModifier_NONE, puma::nina::InputButtonEvent::Pressed}},
        {TestInputActions::MoveBallSpawnerStopUp,       {puma::nina::KeyboardKey::KB_W, puma::InputModifier_NONE, puma::nina::InputButtonEvent::Released}},
        {TestInputActions::MoveBallSpawnerStopDown,     {puma::nina::KeyboardKey::KB_S, puma::InputModifier_NONE, puma::nina::InputButtonEvent::Released}},
        {TestInputActions::MoveBallSpawnerStopLeft,     {puma::nina::KeyboardKey::KB_A, puma::InputModifier_NONE, puma::nina::InputButtonEvent::Released}},
        {TestInputActions::MoveBallSpawnerStopRight,    {puma::nina::KeyboardKey::KB_D, puma::InputModifier_NONE, puma::nina::InputButtonEvent::Released}},
    };

    static const InputActionKeyboardPairList kSpawner1KeyboardInput =
    {
        {TestInputActions::SpawnBallAction,             {puma::nina::KeyboardKey::KB_RCTRL,    puma::InputModifier_IGNORE, puma::nina::InputButtonEvent::Pressed}},
        {TestInputActions::MoveBallSpawnerStartUp,      {puma::nina::KeyboardKey::KB_UP,       puma::InputModifier_NONE, puma::nina::InputButtonEvent::Pressed}},
        {TestInputActions::MoveBallSpawnerStartDown,    {puma::nina::KeyboardKey::KB_DOWN,     puma::InputModifier_NONE, puma::nina::InputButtonEvent::Pressed}},
        {TestInputActions::MoveBallSpawnerStartLeft,    {puma::nina::KeyboardKey::KB_LEFT,     puma::InputModifier_NONE, puma::nina::InputButtonEvent::Pressed}},
        {TestInputActions::MoveBallSpawnerStartRight,   {puma::nina::KeyboardKey::KB_RIGHT,    puma::InputModifier_NONE, puma::nina::InputButtonEvent::Pressed}},
        {TestInputActions::MoveBallSpawnerStopUp,       {puma::nina::KeyboardKey::KB_UP,       puma::InputModifier_NONE, puma::nina::InputButtonEvent::Released}},
        {TestInputActions::MoveBallSpawnerStopDown,     {puma::nina::KeyboardKey::KB_DOWN,     puma::InputModifier_NONE, puma::nina::InputButtonEvent::Released}},
        {TestInputActions::MoveBallSpawnerStopLeft,     {puma::nina::KeyboardKey::KB_LEFT,     puma::InputModifier_NONE, puma::nina::InputButtonEvent::Released}},
        {TestInputActions::MoveBallSpawnerStopRight,    {puma::nina::KeyboardKey::KB_RIGHT,    puma::InputModifier_NONE, puma::nina::InputButtonEvent::Released}},
    };

    static const InputActionControllerPairList kSpawner0ControllerJoystickInput =
    {
        {TestInputActions::MoveBallSpawner,             {puma::nina::ControllerJoystick::CJ_LSTICK, 0}},
    };

    static const InputActionControllerPairList kSpawner1ControllerJoystickInput =
    {
        {TestInputActions::MoveBallSpawner,             {puma::nina::ControllerJoystick::CJ_RSTICK, 0}},
    };

    static const InputActionControllerButtonPairList kSpawner0ControllerButtonInput =
    {
        {TestInputActions::SpawnBallAction,             {puma::nina::ControllerButton::CB_LB, 0, puma::nina::InputButtonEvent::Pressed}},
    };

    static const InputActionControllerButtonPairList kSpawner1ControllerButtonInput =
    {
        {TestInputActions::SpawnBallAction,             {puma::nina::ControllerButton::CB_RB, 0, puma::nina::InputButtonEvent::Pressed}},
    };
}