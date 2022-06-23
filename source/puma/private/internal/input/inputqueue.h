#pragma once

#include <internal/input/inputbuffer.h>
#include <utils/multithreadbuffer.h>

namespace puma
{
    class InputQueue
    {
    public:

        InputQueue();

        void registerInputListener();
        void unregisterInputListener();

        bool updateWriteBuffer();
        bool updateReadBuffer() { return m_inputBuffer.updateReadBuffer(); }

        const InputBuffer* read() const { return m_inputBuffer.read(); }
        InputBuffer* write() { return m_inputBuffer.write(); }

        ModifierBitmask getModifiers( NinaKeyboardKey _key ) const;
        ModifierBitmask getModifiers() const;

        void printInputs() const;

    private:

        MultiThreadBuffer<InputBuffer> m_inputBuffer;

    };
}