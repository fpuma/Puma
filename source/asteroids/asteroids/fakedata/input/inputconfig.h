#pragma once

#include <engine/input/inputdefinitions.h>

struct AsteroidsInputActions
{
    static const puma::InputAction MoveShip;
};

using InputActionControllerJoystickPairList = std::initializer_list<std::pair<puma::InputAction, puma::ControllerJoystickInput>>;

static const InputActionControllerJoystickPairList kShipControllerJoystickInput =
{
    {AsteroidsInputActions::MoveShip, {puma::ControllerJoystick::LEFT_STICK, 0}},
};