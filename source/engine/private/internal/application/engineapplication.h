#pragma once

#include <application/iapplication.h>
#include <engine/application/iengineapplication.h>

namespace puma
{
    class EngineApplication : public IEngineApplication
    {
    public:

        EngineApplication();

        void init( Extent _windowExtent, const char* _windowName ) override;
        void uninit() override;
        void update() override { m_application->update(); }
        AppWindow* getWindow() const override { return m_window; }
        AppTextureManager* getTextureManager() const override { return m_textureManager; }
        AppInput* getInput() const override { return m_input.get(); }

        bool shouldQuit() const { return m_application->shouldQuit(); }
        app::IRenderer* getRenderer() const { return m_renderer; }

    private:

        std::unique_ptr<app::IApplication> m_application;
        std::unique_ptr<input::IInput> m_input = nullptr;

        app::IWindow* m_window = nullptr;
        app::ITextureManager* m_textureManager = nullptr;
        app::IRenderer* m_renderer = nullptr;
    };
}
