#pragma once

#include <time/syncedtimersreference.h>

namespace puma
{
    class TimerProvider
    {
    public:
        
        void update() { m_timersReference.update(); }

        SyncedTimer getTimer() const { return m_timersReference.getTimer(); }
        SyncedCountdownTimer getCountdownTimer() const { return m_timersReference.getCountdownTimer(); }

    private:

        SyncedTimersReference m_timersReference;
    };
}