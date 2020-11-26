#pragma once
#include <engine/ecs/base/providers/ientityprovider.h>

namespace puma
{
    class EntityProvider final : public IEntityProvider
    {
    public:
        EntityProvider() {}

        void init( u32 _entityCount ) override;
        void uninit() override;

        Entity requestEntity() override;
        void disposeEntity( const Entity& _entity ) override;

        void enableEntity( const Entity& _entity ) override;
        void disableEntity( const Entity& _entity ) override;
        bool isEntityEnabled( const Entity& _entity ) const override;

    private:

        enum class EntityStatus
        {
            Enabled,
            Disabled,
            Unassigned
        };

        std::vector<EntityStatus> m_entities;
    };

}
