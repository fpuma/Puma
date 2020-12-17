#pragma once

#include <engine/services/iapplicationservice.h>

namespace puma
{
    class ApplicationService final : public IApplicationService
    {
    public:
        
        ApplicationService() { m_graphics = app::IApplication::create(); }

        ~ApplicationService() { m_graphics.reset(); }

        app::IApplication* get() override { return m_graphics.get(); }

        void uninit() { m_graphics->uninit(); }

    private:

        std::unique_ptr<app::IApplication> m_graphics;
    };

}