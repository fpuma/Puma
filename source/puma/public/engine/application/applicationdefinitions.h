#pragma once

#include <nina/input/inputids.h>
#include <nina/texturemanager/itexturemanager.h>

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
}
