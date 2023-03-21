#pragma once

#include <engine/application/iengineapplication.h>

namespace puma
{
    namespace nina
    {
        class IApplication;
        class IInput;
        class ITextureManager;
        class IWindow;
        class IRenderer;
    }

    class EngineApplication : public IEngineApplication
    {
    public:

        EngineApplication();
        ~EngineApplication();

        void init( Extent _windowExtent, const char* _windowName );
        void uninit();
        void update();
        nina::ITextureManager* getTextureManager() const override;
        
        void setWindowSize( s32 _width, s32 _height ) override;
        void setWindowPosition( s32 _x, s32 _y ) override;
        void setWindowTitle( const char* _title ) override;
        Extent getWindowExtent() const;
        const nina::IRenderer* getWindowRenderer() const;

        const nina::IInput* getInput() const;
        nina::IInput* getInput();

        void setCameraEntity( pina::Entity _cameraEntity ) override;
        pina::Entity getCameraEntity() const;

        bool shouldQuit() const;

    private:

        std::unique_ptr<nina::IApplication> m_application;
        std::unique_ptr<nina::IInput> m_input;

        nina::IWindow* m_window;
        nina::ITextureManager* m_textureManager;
        nina::IRenderer* m_renderer;
        pina::Entity m_cameraEntity;
    };
}
