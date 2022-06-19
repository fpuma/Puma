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

        void updateModifiers();
        ModifierBitmask getModifiers() const { return m_modifierBitmask; }

        void printInputs();

    private:

        InputBuffer* m_toRead = nullptr;
        InputBuffer* m_nextToRead = nullptr;
        InputBuffer* m_toWrite = nullptr;
        InputBuffer* m_nextToWrite = nullptr;

        InputBuffer m_buffer0;
        InputBuffer m_buffer1;
        InputBuffer m_buffer2;

        ModifierBitmask m_modifierBitmask;

        std::mutex m_bufferSyncMutex;

    };
}