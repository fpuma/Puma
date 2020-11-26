#pragma once

#include <engine/services/base/iprovider.h>
#include <time/syncedtimersreference.h>

namespace puma
{
    class TimerProvider final : public IProvider
    {
    public:
        
        void uninit() override {}

        void update() { m_timersReference.update(); }

        SyncedTimer getTimer() const { return m_timersReference.getTimer(); }
        SyncedCountdownTimer getCountdownTimer() const { return m_timersReference.getCountdownTimer(); }

    private:

        SyncedTimersReference m_timersReference;
    };
}