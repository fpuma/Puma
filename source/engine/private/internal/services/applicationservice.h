#pragma once

#include <engine/services/base/iservice.h>
#include <application/iapplication.h>

namespace puma
{
    class ApplicationService final : public IService
    {
    public:
        
        ApplicationService() { m_application = app::IApplication::create(); }

        ~ApplicationService() { m_application.reset(); }

        app::IApplication* get() { return m_application.get(); }

        void uninit() { m_application->uninit(); }

    private:

        std::unique_ptr<app::IApplication> m_application;
    };

}

#include <engine/services/base/iservicecontainer.h>

#define gApplication puma::DefaultServices::getInstance()->get<puma::ApplicationService>()->get()