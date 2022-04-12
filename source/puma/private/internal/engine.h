#pragma once

#include <engine/iengine.h>
#include <time/deltatime.h>
#include <internal/renderer/enginerenderer.h>

namespace puma
{

    class ServiceContainer;

    class Engine : public IEngine
    {
    public:

        void run( std::unique_ptr<IGame>&& _game ) override;

        void init( const Extent _windowExtent = { 1280,720,200,200 }, const char* _windowName = "Puma" );
        void uninit();

        void update();
        void render();

        bool shouldQuit() const { return m_shouldQuit; }

    private:

        std::unique_ptr<IGame> m_game = nullptr;
        std::unique_ptr<ServiceContainer> m_services = nullptr;
        EngineRenderer m_engineRenderer;
        DeltaTime m_deltaTime;
        bool m_shouldQuit = false;
    };
}