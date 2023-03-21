#pragma once

#include <engine/layers/ilayer.h>
#include <engine/services/base/iservice.h>
#include <utils/containers/uniquerealizationcontainer.h>

namespace puma
{
	
	class ILayerManager : public UniqueRealizationContainer<ILayer>, public IService
	{
	public:
		virtual ~ILayerManager() {}
	};
}