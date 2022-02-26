#pragma once

#include <application/iwindow.h>
#include <application/irenderer.h>
#include <input/devices/icontroller.h>
#include <input/devices/ikeyboard.h>
#include <input/devices/imouse.h>
#include <input/iinput.h>
#include <input/inputids.h>
#include <texturemanager/itexturemanager.h>

namespace puma
{
    using AppTextureManager = app::ITextureManager;
    using AppInput = app::IInput;
    using AppWindow = app::IWindow;
    using AppRenderer = app::IRenderer;
    using AppTexture = app::Texture;
    using AppTextureSample = app::TextureSample;
    
    using AppInputId = app::InputId;
    using AppKeyboardKey = app::KeyboardKey;
    using AppMouseButton = app::MouseButton;
    using AppMouseWheel = app::MouseWheelState;
    
    using AppControllerButton = app::ControllerButton;
    using AppControllerTrigger = app::ControllerTrigger;
    using AppControllerId = app::ControllerId;
    
    using AppController = app::IController;
    using AppKeyboard = app::IKeyboard;
    using AppMouse = app::IMouse;
}
