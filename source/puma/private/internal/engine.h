#pragma once

#include <engine/iengine.h>
#include <time/deltatime.h>
#include <internal/renderer/enginerenderer.h>

namespace puma
{

    class ServiceContainer;
    class IGame;

    class Engine : public IEngine
    {
    public:

        void init( const Extent _windowExtent = { 1280,720,200,200 }, const char* _windowName = "Puma" );
        void uninit();

        void simulationUpdate(IGame* _game);
        void applicationUpdate();

        bool shouldQuit() const { return m_shouldQuit; }

        void updateThread( IGame* _game );
        
    private:

        void render();

        std::unique_ptr<IGame> m_game = nullptr;
        std::unique_ptr<ServiceContainer> m_services = nullptr;
        EngineRenderer m_engineRenderer;
        DeltaTime m_deltaTime;
        DeltaTime m_appDt;
        
        float m_simulationMinStep = 0.004f;
        float m_accumDeltaTime = 0.0f;

        bool m_shouldQuit = false;
    };
}