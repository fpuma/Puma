#pragma once

#include <application/iapplication.h>
#include <engine/application/iengineapplication.h>
#include <engine/application/applicationdefinitions.h>


namespace puma
{
    namespace nina
    {
        class IInput;
        class ITextureManager;
        class IWindow;
    }

    using NinaInput = nina::IInput;
    using NinaWindow = nina::IWindow;

    class EngineApplication : public IEngineApplication
    {
    public:

        EngineApplication();

        void init( Extent _windowExtent, const char* _windowName ) override;
        void uninit() override;
        void update() override { m_application->update(); }
        NinaTextureManager* getTextureManager() const override { return m_textureManager; }
        
        NinaWindow* getWindow() const { return m_window; }
        NinaInput* getInput() const { return m_input.get(); }

        void setCameraEntity( Entity _cameraEntity ) override;
        Entity getCameraEntity() const { return m_cameraEntity; }

        bool shouldQuit() const { return m_application->shouldQuit(); }
        NinaRenderer* getRenderer() const { return m_renderer; }

    private:

        std::unique_ptr<nina::IApplication> m_application = nullptr;
        std::unique_ptr<NinaInput> m_input = nullptr;

        NinaWindow* m_window = nullptr;
        NinaTextureManager* m_textureManager = nullptr;
        NinaRenderer* m_renderer = nullptr;
        Entity m_cameraEntity = kInvalidEntity;
    };
}
