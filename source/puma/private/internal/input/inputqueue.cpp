#include "precompiledengine.h"

#include "inputqueue.h"
#include <input/iinputlistener.h>
#include <internal/services/engineapplicationservice.h>
#include <input/iinput.h>
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

        void onKeyboardKey( NinaKeyboardKey _key ) const override
        {
            const auto* input = gInternalEngineApplication->getInput();
            const auto& keyboard = input->getKeyboard();

            KeyboardInput kbInput;
            kbInput.keyboardKey = _key;
            kbInput.modifiers = m_queue->getModifiers();
            assert( keyboard.keyPressed( _key ) || keyboard.keyReleased( _key ) ); //If we reach this point one of these events must have happened
            kbInput.state = keyboard.keyPressed( _key ) ? InputState::Pressed : InputState::Released;

            m_queue->write()->addKeyboardInput( std::move(kbInput) );
        }

        void onMouseButton( NinaMouseButton _button ) const override
        {
            const auto* input = gInternalEngineApplication->getInput();
            const auto& mouse = input->getMouse();

            MouseButtonInput mbInput;
            mbInput.mouseButton = _button;
            mbInput.modifiers = m_queue->getModifiers();
            assert( mouse.buttonPressed( _button ) || mouse.buttonReleased( _button ) ); //If we reach this point one of these events must have happened
            mbInput.state = mouse.buttonPressed( _button ) ? InputState::Pressed : InputState::Released;

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
            const auto* input = gInternalEngineApplication->getInput();
            const auto& mouse = input->getMouse();

            MousePositionInput mpInput;
            mpInput.modifiers = m_queue->getModifiers();
            auto mousePosition = mouse.getMousePosition();
            m_queue->write()->setMousePosition( std::move( mpInput ), { static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y) } );
        }

        void onControllerButton( nina::ControllerId _id, nina::ControllerButton _buttonId ) const override
        {
            ControllerButtonInput cbInput;
            cbInput.controllerId = _id;
            cbInput.controllerButton = _buttonId;

            m_queue->write()->addControllerButtonInput( std::move(cbInput) );
        }

        void onControllerJoystick( nina::ControllerId _id, nina::ControllerJoystickAxis _joystickId, float _joystickValue ) const override
        {
            ControllerJoystickInput cjInput;
            cjInput.controllerId = _id;

            if (_joystickId == nina::ControllerJoystickAxis::CJ_LSTICK_X ||
                _joystickId == nina::ControllerJoystickAxis::CJ_LSTICK_Y)
            {
                cjInput.controllerJoystick = ControllerJoystick::LEFT_STICK;
            }
            else
            {
                cjInput.controllerJoystick = ControllerJoystick::RIGHT_STICK;;
            }

            InputActionExtraInfo extraInfo;

            if (_joystickId == nina::ControllerJoystickAxis::CJ_LSTICK_X ||
                _joystickId == nina::ControllerJoystickAxis::CJ_RSTICK_X)
            {
                extraInfo.x = _joystickValue;
            }
            else
            {
                extraInfo.y = _joystickValue;
            }

            m_queue->write()->setJoystickInput( std::move( cjInput ), std::move( extraInfo ) );
        }

        void onControllerTrigger( nina::ControllerId _id, nina::ControllerTrigger _triggerId, float _triggerValue ) const override
        {
            const auto* input = gInternalEngineApplication->getInput();
            const auto& controller = input->getController( _id );

            ControllerTriggerInput ctInput;
            ctInput.controllerId = _id;
            ctInput.controllerTrigger = _triggerId;
            float triggerValue = _triggerId == NinaControllerTrigger::CT_LTRIGGER ? controller.getLeftTrigger() : controller.getRightTrigger();
            m_queue->write()->setControllerTriggerInput( std::move( ctInput ), { triggerValue, 0.0f } );
        }

    private:

        InputQueue* m_queue;
    };

    InputQueue::InputQueue()
        : m_toRead( &m_buffer0 )
        , m_nextToRead( nullptr )
        , m_toWrite( &m_buffer1 )
        , m_nextToWrite( &m_buffer2 )
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

    void InputQueue::updateModifiers()
    {
        m_modifierBitmask = 0;
        const auto* input = gInternalEngineApplication->getInput();
        const auto& keyboard = input->getKeyboard();

        if (keyboard.keyState( NinaKeyboardKey::KB_LSHIFT )) m_modifierBitmask |= InputModifier_LSHIFT;
        if (keyboard.keyState( NinaKeyboardKey::KB_RSHIFT )) m_modifierBitmask |= InputModifier_RSHIFT;
        if (keyboard.keyState( NinaKeyboardKey::KB_LCTRL  )) m_modifierBitmask |= InputModifier_LCTRL;
        if (keyboard.keyState( NinaKeyboardKey::KB_RCTRL  )) m_modifierBitmask |= InputModifier_RCTRL;
        if (keyboard.keyState( NinaKeyboardKey::KB_LALT   )) m_modifierBitmask |= InputModifier_LALT;
        if (keyboard.keyState( NinaKeyboardKey::KB_RALT   )) m_modifierBitmask |= InputModifier_RALT;
    }

    bool InputQueue::updateWriteBuffer()
    {
        std::lock_guard<std::mutex> guard( m_bufferSyncMutex );
        bool update = nullptr != m_nextToWrite;
        if (update)
        {
            assert( nullptr == m_nextToRead ); //If nextToWrite is available, then nextToRead should be nullptr
            std::swap( m_toWrite, m_nextToRead );
            std::swap( m_toWrite, m_nextToWrite );
            m_toWrite->clear();
        }
        return update;
    }

    bool InputQueue::updateReadBuffer()
    {
        std::lock_guard<std::mutex> guard( m_bufferSyncMutex );
        bool update = nullptr != m_nextToRead;
        if (update)
        {
            assert( nullptr == m_nextToWrite ); //If nextToRead is available, nextToWrite must be nullptr
            std::swap( m_toRead, m_nextToWrite );
            std::swap( m_toRead, m_nextToRead );
        }
        return update;
    }

    void InputQueue::printInputs()
    {
        m_toRead->printToLog();
    }


}