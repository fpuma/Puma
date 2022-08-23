#pragma once

#include <pina/private/entityprovider.h>

namespace puma
{
    class EntityProvider : public pina::EntityProvider
    {
        EntityProvider( pina::EcsData& _data )
            : pina::EntityProvider( _data ) {}
    };
}