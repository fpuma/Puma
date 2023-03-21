#pragma once

#include <engine/services/ilayersservice.h>
#include <internal/layers/layermanager.h>

namespace puma
{
    class LayersService : public ILayersService
    {
    public:

        virtual ~LayersService() {}

        LayerManager* get() override { return &m_layerManager; };

    private:

        LayerManager m_layerManager;
    };
}

//#include <engine/services/base/iservicecontainer.h>
//
//#define gLayers puma::DefaultServices::getInstance()->get<puma::ILayersService>()->get()