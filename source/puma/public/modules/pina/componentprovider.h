#pragma once

#include <pina/private/componentprovider.h>

namespace puma
{
    class ComponentProvider : public pina::ComponentProvider
    {
        ComponentProvider( pina::EcsData& _data)
            : pina::ComponentProvider( _data ) {}
    };
}