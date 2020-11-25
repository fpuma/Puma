#pragma once

#include <engine/services/itimeservice.h>

namespace puma
{
    class TimeService final : public ITimeService
    {
    public:
        
        TimeService() { m_timeReference = ITimeReference::create(); }

        ~TimeService() { m_timeReference.reset(); }

        ITimeReference* get() override { return m_timeReference.get(); }

        void uninit() {}

    private:

        std::unique_ptr<ITimeReference> m_timeReference;
    };

}