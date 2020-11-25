#pragma once

#include <engine/services/base/iprovider.h>
#include <engine/services/itimeservice.h>
#include <time/itimermanager.h>
#include <time/itimereference.h>

namespace puma
{
    class TimerProvider : public IProvider
    {
    public:

        TimerProvider() 
        { 
            m_timerManager = ITimerManager::create( []() { return (float)gTime->getExecutionTimeInSeconds(); } );
        }

        void uninit() override {}

        TimerID requestNewTimer() { return m_timerManager->requestNewTimer(); }
        CountdownTimerID requestNewCountdownTimer() { return m_timerManager->requestNewCountdownTimer(); }

        void disposeTimer( TimerID _id ) { m_timerManager->disposeTimer( _id ); }
        void disposeCountdownTimer( CountdownTimerID _id ) { m_timerManager->disposeCountdownTimer( _id ); }

        ITimer* getTimer( TimerID _id ) { return m_timerManager->getTimer( _id ); }
        ICountdownTimer* getCountdownTimer( CountdownTimerID _id ) { return m_timerManager->getCountdownTimer( _id ); }

        void clear() { m_timerManager->clear(); }

    private:

        std::unique_ptr<ITimerManager> m_timerManager;
    };
}