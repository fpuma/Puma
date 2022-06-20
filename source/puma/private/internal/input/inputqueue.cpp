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
            const auto* input = gInternalEngineApplication->getInput();
            const auto& controller = input->getController( _id );

            ControllerButtonInput cbInput;
            cbInput.controllerId = _id;
            cbInput.controllerButton = _buttonId;
            cbInput.state = controller.buttonPressed( _buttonId ) ? InputState::Pressed : InputState::Released;
            m_queue->write()->addControllerButtonInput( std::move(cbInput) );
        }

        void onControllerJoystick( nina::ControllerId _id, nina::ControllerJoystickAxis _joystickId, float _joystickValue ) const override
        {
            const auto* input = gInternalEngineApplication->getInput();
            const auto& controller = input->getController( _id );

            ControllerJoystickInput cjInput;
            InputActionExtraInfo extraInfo;
            
            cjInput.controllerId = _id;

            if (_joystickId == nina::ControllerJoystickAxis::CJ_LSTICK_X ||
                _joystickId == nina::ControllerJoystickAxis::CJ_LSTICK_Y)
            {
                cjInput.controllerJoystick = ControllerJoystick::LEFT_STICK;
                nina::JoystickPosition jPos = controller.getLeftJoystickPosition();
                extraInfo = { jPos.x, jPos.y };
            }
            else
            {
                cjInput.controllerJoystick = ControllerJoystick::RIGHT_STICK;
                nina::JoystickPosition jPos = controller.getRightJoystickPosition();
                extraInfo = { jPos.x, jPos.y };
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

    ModifierBitmask InputQueue::getModifiers() const
    {
        char result = 0;
        const auto* input = gInternalEngineApplication->getInput();
        const auto& keyboard = input->getKeyboard();

        if (keyboard.keyState( NinaKeyboardKey::KB_LSHIFT )) result |= InputModifier_LSHIFT;
        if (keyboard.keyState( NinaKeyboardKey::KB_RSHIFT )) result |= InputModifier_RSHIFT;
        if (keyboard.keyState( NinaKeyboardKey::KB_LCTRL  )) result |= InputModifier_LCTRL;
        if (keyboard.keyState( NinaKeyboardKey::KB_RCTRL  )) result |= InputModifier_RCTRL;
        if (keyboard.keyState( NinaKeyboardKey::KB_LALT   )) result |= InputModifier_LALT;
        if (keyboard.keyState( NinaKeyboardKey::KB_RALT   )) result |= InputModifier_RALT;

        return result;
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