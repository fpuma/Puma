#pragma once

#include <engine/ecs/base/isystem.h>
#include <utils/containers/uniquerealizationcontainer.h>

namespace puma
{
    class ISystemContainer : public UniqueRealizationContainer<ISystem>, public NonCopyable
    {
    public:
        virtual ~ISystemContainer(){}

        virtual void updateSystemsProperties() = 0;
    };
}