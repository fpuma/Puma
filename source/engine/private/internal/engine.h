#pragma once

#include <engine/iengine.h>
#include <time/deltatime.h>

namespace puma
{

    class ServiceContainer;

    class Engine : public IEngine
    {
    public:

        void init() override;
        void uninit() override;

        void update() override;
        void render() override;

        bool shouldQuit() const override { return m_shouldQuit; }

    private:

        std::unique_ptr<ServiceContainer> m_services = nullptr;
        DeltaTime m_deltaTime;
        bool m_shouldQuit = false;
    };
}