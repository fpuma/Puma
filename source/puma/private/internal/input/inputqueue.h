#pragma once

#include <internal/input/inputbuffer.h>
#include <mutex>
#include <bitset>

namespace puma
{
    class InputQueue
    {
    public:

        InputQueue();

        void registerInputListener();
        void unregisterInputListener();

        bool updateWriteBuffer();
        bool updateReadBuffer();

        const InputBuffer* read() const { return m_toRead; }
        InputBuffer* write() { return m_toWrite; }

        ModifierBitmask getModifiers( NinaKeyboardKey _key ) const;
        ModifierBitmask getModifiers() const;

        void printInputs();

    private:

        InputBuffer* m_toRead = nullptr;
        InputBuffer* m_nextToRead = nullptr;
        InputBuffer* m_toWrite = nullptr;
        InputBuffer* m_nextToWrite = nullptr;

        InputBuffer m_buffer0;
        InputBuffer m_buffer1;
        InputBuffer m_buffer2;

        std::mutex m_bufferSyncMutex;

    };
}