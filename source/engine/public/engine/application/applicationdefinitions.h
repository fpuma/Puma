#pragma once

#include <input/devices/icontroller.h>
#include <input/devices/ikeyboard.h>
#include <input/devices/imouse.h>
#include <input/inputids.h>
#include <texturemanager/itexturemanager.h>

namespace puma
{
    
    using NinaRenderer = nina::IRenderer;
    using NinaTextureManager = nina::ITextureManager;
    using NinaTexture = nina::Texture;
    using NinaTextureSample = nina::TextureSample;
    
    using NinaInputId = nina::InputId;
    using NinaKeyboardKey = nina::KeyboardKey;
    using NinaMouseButton = nina::MouseButton;
    using NinaMouseWheel = nina::MouseWheelState;
    
    using NinaControllerButton = nina::ControllerButton;
    using NinaControllerTrigger = nina::ControllerTrigger;
    using NinaControllerId = nina::ControllerId;
    
    using NinaController = nina::IController;
    using NinaKeyboard = nina::IKeyboard;
    using NinaMouse = nina::IMouse;
}
