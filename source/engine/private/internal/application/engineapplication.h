#pragma once

#include <application/iapplication.h>
#include <engine/application/iengineapplication.h>
#include <engine/application/applicationdefinitions.h>


namespace puma
{
    namespace app
    {
        class IInput;
        class ITextureManager;
        class IWindow;
    }

    using AppInput = app::IInput;
    using AppTextureManager = app::ITextureManager;
    using AppWindow = app::IWindow;

    class EngineApplication : public IEngineApplication
    {
    public:

        EngineApplication();

        void init( Extent _windowExtent, const char* _windowName ) override;
        void uninit() override;
        void update() override { m_application->update(); }
        AppTextureManager* getTextureManager() const override { return m_textureManager; }
        
        AppWindow* getWindow() const { return m_window; }
        AppInput* getInput() const { return m_input.get(); }

        void setCameraEntity( Entity _cameraEntity ) override;
        Entity getCameraEntity() const { return m_cameraEntity; }

        bool shouldQuit() const { return m_application->shouldQuit(); }
        AppRenderer* getRenderer() const { return m_renderer; }

    private:

        std::unique_ptr<app::IApplication> m_application = nullptr;
        std::unique_ptr<AppInput> m_input = nullptr;

        AppWindow* m_window = nullptr;
        AppTextureManager* m_textureManager = nullptr;
        AppRenderer* m_renderer = nullptr;
        Entity m_cameraEntity = kInvalidEntity;
    };
}
