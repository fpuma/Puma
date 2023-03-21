#pragma once

#include <engine/layers/ilayermanager.h>

namespace puma
{
	
	class LayerManager : public ILayerManager
	{
	public:
		virtual ~LayerManager() {}

	protected:

		void onAdded( std::shared_ptr<ILayer> _system, std::type_index _typeIndex ) override;
		void onRemoved( std::shared_ptr<ILayer> _system, std::type_index _typeIndex ) override;

	};
}