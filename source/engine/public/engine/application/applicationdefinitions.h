#pragma once

#include <application/iwindow.h>
#include <input/iinput.h>
#include <texturemanager/itexturemanager.h>

namespace puma
{
    using AppTextureManager = app::ITextureManager;
    using AppInput = input::IInput;
    using AppWindow = app::IWindow;
}
