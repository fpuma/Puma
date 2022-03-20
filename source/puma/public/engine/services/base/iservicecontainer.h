#pragma once

#include <engine/services/base/iservice.h>

#include <utils/containers/uniquerealizationcontainer.h>

namespace puma
{
    class IServiceContainer : public UniqueRealizationContainer<IService>, public NonCopyable
    {
    public:

        virtual ~IServiceContainer() {}
    };

    using DefaultServices = DefaultInstance<IServiceContainer>;
}