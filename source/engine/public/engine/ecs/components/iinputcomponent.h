#pragma once

#include <engine/ecs/base/icomponent.h>
#include <engine/input/inputdefinitions.h>

namespace puma
{
    class IInputComponent : public IComponent
    {
    public:

        virtual ~IInputComponent() {}

        virtual void addInputMap( InputAction _inputAction, MouseButtonInput _mouseButtonInput ) = 0;
        virtual void addInputMap( InputAction _inputAction, MouseWheelInput _mouseWheelInput ) = 0;
        virtual void addInputMap( InputAction _inputAction, KeyboardInput _keyboardInput ) = 0;
        virtual void addInputMap( InputAction _inputAction, ControllerButtonInput _controllerButtonInput ) = 0;
        virtual void addInputMap( InputAction _inputAction, ControllerTriggerInput _controllerTriggerInput ) = 0;

        virtual void enableAction( InputAction _inputAction ) = 0;
        virtual void disableAction( InputAction _inputAction ) = 0;

        virtual bool isActionActive( InputAction _inputAction ) const = 0;
    };
}