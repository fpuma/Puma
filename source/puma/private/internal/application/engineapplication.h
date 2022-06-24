#pragma once

#include <nina/application/iapplication.h>
#include <engine/application/iengineapplication.h>
#include <engine/external/ninadefinitions.h>


namespace puma
{
    namespace nina
    {
        class IInput;
        class ITextureManager;
        class IWindow;
    }

    class EngineApplication : public IEngineApplication
    {
    public:

        EngineApplication();

        void init( Extent _windowExtent, const char* _windowName );
        void uninit();
        void update() { m_application->update(); }
        nina::ITextureManager* getTextureManager() const override { return m_textureManager; }
        
        void setWindowSize( s32 _width, s32 _height ) override;
        void setWindowPosition( s32 _x, s32 _y ) override;
        void setWindowTitle( const char* _title ) override;
        Extent getWindowExtent() const;
        const nina::IRenderer* getWindowRenderer() const { return m_renderer; }

        const nina::IInput* getInput() const { return m_input.get(); }
        nina::IInput* getInput() { return m_input.get(); }

        void setCameraEntity( Entity _cameraEntity ) override;
        Entity getCameraEntity() const { return m_cameraEntity; }

        bool shouldQuit() const { return m_application->shouldQuit(); }

    private:

        std::unique_ptr<nina::IApplication> m_application = nullptr;
        std::unique_ptr<nina::IInput> m_input = nullptr;

        nina::IWindow* m_window = nullptr;
        nina::ITextureManager* m_textureManager = nullptr;
        nina::IRenderer* m_renderer = nullptr;
        Entity m_cameraEntity;
    };
}
