#pragma once

#include <engine/services/base/iservice.h>
#include <graphics/igraphics.h>

namespace puma
{
    class IGraphicsService : public IService
    {
    public:
        
        virtual ~IGraphicsService() {}

        virtual gfx::IGraphics* get() = 0;
    };
}

#include <engine/services/base/iservicecontainer.h>

#define gGraphics puma::DefaultServices::getInstance()->get<puma::IGraphicsService>()->get()