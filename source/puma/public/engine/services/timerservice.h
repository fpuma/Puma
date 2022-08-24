#pragma once

#include <engine/utils/timerprovider.h>
#include <engine/services/base/iservice.h>
#include <memory>
namespace puma
{
    class TimerService : public IService
    {
    public:

        TimerService()
            : m_timers( std::make_unique<TimerProvider>() ) 
        {}

        virtual ~TimerService() { m_timers.reset(); }

        TimerProvider* get() { return m_timers.get(); };

    private:

        std::unique_ptr<TimerProvider> m_timers;
    };
}

#include <engine/services/base/iservicecontainer.h>

#define gProviders puma::DefaultServices::getInstance()->get<puma::TimerService>()->get()