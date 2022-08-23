#pragma once

#include <engine/ecs/components/iinputcomponent.h>
#include <internal/input/inputmap.h>

namespace puma
{
    class InputBuffer;

    class InputComponent final : public IInputComponent
    {
    public:

        void addInputMap( InputAction _inputAction, MousePositionInput _mousePositionInput ) override;
        void addInputMap( InputAction _inputAction, MouseButtonInput _mouseButtonInput ) override;
        void addInputMap( InputAction _inputAction, MouseWheelInput _mouseWheelInput ) override;
        void addInputMap( InputAction _inputAction, KeyboardInput _keyboardInput ) override;
        void addInputMap( InputAction _inputAction, ControllerButtonInput _controllerButtonInput ) override;
        void addInputMap( InputAction _inputAction, ControllerTriggerInput _controllerTriggerInput ) override;
        void addInputMap( InputAction _inputAction, ControllerJoystickInput _controllerJoystickInput ) override;

        void enableAction( InputAction _inputAction ) override;
        void disableAction( InputAction _inputAction ) override;

        bool isActionActive( InputAction _inputAction ) const override;

        InputActionExtraInfo getInputActionExtraInfo( InputAction _inputAction ) const override;

        void evaluate( const InputBuffer& _inputBuffer );

        void clearActiveActions();

    private:

        struct ExtraInfoData
        {
            InputAction inputAction;
            InputActionExtraInfo extraInfo;

            bool operator < ( const ExtraInfoData& _other ) const
            {
                return inputAction < _other.inputAction;
            }
        };

        std::set<InputAction> m_activeAction;
        std::set<InputMap> m_inputMaps;
        std::set<InputAction> m_disabledActions;
        std::set<ExtraInfoData> m_extraInfo;

    };
}