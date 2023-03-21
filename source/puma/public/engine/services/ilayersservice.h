#pragma once

#include <engine/services/base/iservice.h>
#include <engine/layers/ilayermanager.h>

namespace puma
{
    class ILayersService : public IService
    {
    public:

        virtual ~ILayersService() {}

        virtual ILayerManager* get() = 0;

    };
}

#include <engine/services/base/iservicecontainer.h>

#define gLayers puma::DefaultServices::getInstance()->get<puma::ILayersService>()->get()