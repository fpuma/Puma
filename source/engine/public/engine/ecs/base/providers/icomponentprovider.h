#pragma once

#include <engine/ecs/base/entity.h>
#include <engine/ecs/base/icomponent.h>
#include <engine/services/base/iprovider.h>
#include <utils/containers/mappedrealizationcontainer.h>

namespace puma
{
    class IComponentProvider : public MappedRealizationContainer<Entity, IComponent>, public IProvider
    {
    public:
        virtual ~IComponentProvider(){}
    };
}