#include "precompiledengine.h"

#include "inputqueue.h"
#include <internal/services/engineapplicationservice.h>
#include <nina/input/iinput.h>
#include <nina/input/iinputlistener.h>
#include <nina/input/devices/icontroller.h>
#include <nina/input/devices/imouse.h>
#include <nina/input/devices/ikeyboard.h>
#include <engine/input/inputdefinitions.h>

namespace puma
{
    class InputListener : public nina::IInputListener
    {
    public:

        InputListener( InputQueue* _queue )
        {
            m_queue = _queue;
        }

        void onKeyboardKey( NinaKeyboardKey _key, NinaInputButtonEvent _event ) const override
        {
            KeyboardInput kbInput;
            kbInput.keyboardKey = _key;
            kbInput.modifiers = m_queue->getModifiers( _key );
            kbInput.state = _event;

            m_queue->write()->addKeyboardInput( std::move(kbInput) );
        }

        void onMouseButton( NinaMouseButton _button, NinaInputButtonEvent _event ) const override
        {
            MouseButtonInput mbInput;
            mbInput.mouseButton = _button;
            mbInput.modifiers = m_queue->getModifiers();
            mbInput.state = _event;

            m_queue->write()->addMouseButton( std::move( mbInput ) );
        }

        void onMouseWheel( NinaMouseWheel _wheelState ) const override
        {
            MouseWheelInput mwInput;
            mwInput.mouseWheel = _wheelState;
            mwInput.modifiers = m_queue->getModifiers();

            m_queue->write()->addMouseWheelInput( std::move( mwInput ) );
        }

        void onMousePosition( nina::MousePosition _mousePosition ) const override
        {
            MousePositionInput mpInput;
            mpInput.modifiers = m_queue->getModifiers();
            auto mousePosition = _mousePosition;
            m_queue->write()->setMousePosition( std::move( mpInput ), { static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y) } );
        }

        void onControllerButton( nina::ControllerId _id, nina::ControllerButton _buttonId, NinaInputButtonEvent _event ) const override
        {
            ControllerButtonInput cbInput;
            cbInput.controllerId = _id;
            cbInput.controllerButton = _buttonId;
            cbInput.state = _event;
            m_queue->write()->addControllerButtonInput( std::move(cbInput) );
        }

        void onControllerJoystick( nina::ControllerId _id, nina::ControllerJoystick _joystickId, nina::JoystickPosition _joystickValue ) const override
        {
            ControllerJoystickInput cjInput;
            InputActionExtraInfo extraInfo;
            
            cjInput.controllerId = _id;
            cjInput.controllerJoystick = _joystickId;
            extraInfo = { _joystickValue.x, _joystickValue.y };

            m_queue->write()->setJoystickInput( std::move( cjInput ), std::move( extraInfo ) );
        }

        void onControllerTrigger( nina::ControllerId _id, nina::ControllerTrigger _triggerId, float _triggerValue ) const override
        {
            ControllerTriggerInput ctInput;
            ctInput.controllerId = _id;
            ctInput.controllerTrigger = _triggerId;
            float triggerValue = _triggerValue;
            m_queue->write()->setControllerTriggerInput( std::move( ctInput ), { triggerValue, 0.0f } );
        }

    private:

        InputQueue* m_queue;
    };

    InputQueue::InputQueue()
    {
    }

    void InputQueue::registerInputListener()
    {
        gInternalEngineApplication->getInput()->setInputListener( std::move( std::make_unique<InputListener>( this ) ) );
    }

    void InputQueue::unregisterInputListener()
    {
        gInternalEngineApplication->getInput()->clearInputListener();
    }

    bool InputQueue::updateWriteBuffer()
    { 
        bool result = m_inputBuffer.updateWriteBuffer();
        if (result)
        {
            m_inputBuffer.write()->clear();
        }
        return result;
    }

    ModifierBitmask InputQueue::getModifiers( NinaKeyboardKey _key ) const
    {
        char result = 0;
        const auto* input = gInternalEngineApplication->getInput();
        const auto& keyboard = input->getKeyboard();

        if ( !(NinaKeyboardKey::KB_LSHIFT == _key) && keyboard.keyState( NinaKeyboardKey::KB_LSHIFT )) result |= InputModifier_LSHIFT;
        if ( !(NinaKeyboardKey::KB_RSHIFT == _key) && keyboard.keyState( NinaKeyboardKey::KB_RSHIFT )) result |= InputModifier_RSHIFT;
        if ( !(NinaKeyboardKey::KB_LCTRL  == _key) && keyboard.keyState( NinaKeyboardKey::KB_LCTRL  )) result |= InputModifier_LCTRL;
        if ( !(NinaKeyboardKey::KB_RCTRL  == _key) && keyboard.keyState( NinaKeyboardKey::KB_RCTRL  )) result |= InputModifier_RCTRL;
        if ( !(NinaKeyboardKey::KB_LALT   == _key) && keyboard.keyState( NinaKeyboardKey::KB_LALT   )) result |= InputModifier_LALT;
        if ( !(NinaKeyboardKey::KB_RALT   == _key) && keyboard.keyState( NinaKeyboardKey::KB_RALT   )) result |= InputModifier_RALT;

        return result;
    }

    ModifierBitmask InputQueue::getModifiers() const
    {
        char result = 0;
        const auto* input = gInternalEngineApplication->getInput();
        const auto& keyboard = input->getKeyboard();

        if ( keyboard.keyState( NinaKeyboardKey::KB_LSHIFT )) result |= InputModifier_LSHIFT;
        if ( keyboard.keyState( NinaKeyboardKey::KB_RSHIFT )) result |= InputModifier_RSHIFT;
        if ( keyboard.keyState( NinaKeyboardKey::KB_LCTRL )) result |= InputModifier_LCTRL;
        if ( keyboard.keyState( NinaKeyboardKey::KB_RCTRL )) result |= InputModifier_RCTRL;
        if ( keyboard.keyState( NinaKeyboardKey::KB_LALT )) result |= InputModifier_LALT;
        if ( keyboard.keyState( NinaKeyboardKey::KB_RALT )) result |= InputModifier_RALT;

        return result;
    }

    void InputQueue::printInputs() const
    {
        m_inputBuffer.read()->printToLog();
    }


}