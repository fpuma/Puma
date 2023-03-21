#pragma once

#include <engine/utils/timerprovider.h>
#include <engine/services/base/iservice.h>

namespace puma
{
    class TimerService final : public IService
    {
    public:

        TimerProvider* get() { return &m_timers; };

    private:

        TimerProvider m_timers;
    };
}

#include <engine/services/base/iservicecontainer.h>

#define gTimers puma::DefaultServices::getInstance()->get<puma::TimerService>()->get()