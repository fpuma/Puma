#pragma once

#include <application/iapplication.h>
#include <engine/application/iengineapplication.h>
#include <engine/application/applicationdefinitions.h>

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
