#pragma once

#include <time/timers/countdowntimer.h>

namespace puma
{
    class Cooldown
    {
    public:

        void setCooldownTime( float _time ) { m_timer.setTimeLimit( _time ); }

        bool cooldownReady()
        {
            bool result = false;
            switch (m_state)
            {
            case State::Ready:
            {
                m_state = State::OnCooldown;
                m_timer.play();
                result = true;
                break;
            }
            case State::OnCooldown:
            {
                if (m_timer.isFinished())
                {
                    m_timer.stop();
                    m_timer.play();
                    result = true;
                }
                break;
            }
            default:
                assert( false ); // Something very wrong happened
            }

            return result;
        }

    private:

        enum class State
        {
            Ready = 0,
            OnCooldown
        } m_state;

        CountdownTimer m_timer;
    };
}