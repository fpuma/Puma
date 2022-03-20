#pragma once
#include <engine/services/base/iprovider.h>
#include <utils/containers/uniquerealizationcontainer.h>

namespace puma
{
    class IProviderContainer : public UniqueRealizationContainer<IProvider>, public NonCopyable
    {
    public:

        virtual ~IProviderContainer(){}
    };
}