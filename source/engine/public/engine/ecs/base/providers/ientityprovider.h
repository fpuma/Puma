#pragma once
#include <engine/ecs/base/entity.h>
#include <engine/services/base/iprovider.h>

namespace puma
{
    class IEntityProvider : public IProvider
    {
    public:
        virtual ~IEntityProvider() {}

        virtual void init( u32 _entityCount ) = 0;

        virtual Entity requestEntity() = 0;
        virtual void disposeEntity( const Entity& _entity ) = 0;

        virtual void enableEntity( const Entity& _entity ) = 0;
        virtual void disableEntity( const Entity& _entity ) = 0;
        virtual bool isEntityEnabled( const Entity& _entity ) const = 0;

    };

}