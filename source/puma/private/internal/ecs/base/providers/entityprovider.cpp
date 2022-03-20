#include <precompiledengine.h>

#include <internal/ecs/base/providers/entityprovider.h>

namespace puma
{
    void EntityProvider::init( u32 _entityCount )
    {
        m_entities.resize( _entityCount, EntityStatus::Unassigned );
    }

    void EntityProvider::uninit()
    {
        assert( std::all_of( m_entities.begin(), m_entities.end(), []( const EntityStatus& _status )
        {
            return _status == EntityStatus::Unassigned;
        } ) );

        m_entities.clear();
    }

    Entity EntityProvider::requestEntity()
    {
        Entity result = kInvalidEntity;

        auto itFoundEntity = std::find( m_entities.begin(), m_entities.end(), EntityStatus::Unassigned );

        if ( m_entities.end() != itFoundEntity )
        {
            result = std::distance( m_entities.begin(), itFoundEntity );
            *itFoundEntity = EntityStatus::Enabled;
        }
        else
        {
            result = m_entities.size();
            m_entities.push_back( EntityStatus::Enabled );
        }

        return result;
    }

    void EntityProvider::disposeEntity( const Entity& _entity )
    {
        assert( m_entities[_entity] != EntityStatus::Unassigned );
        m_entities[_entity] = EntityStatus::Unassigned;
    }

    void EntityProvider::enableEntity(const Entity& _entity)
    {
        assert( m_entities[_entity] != EntityStatus::Unassigned );
        m_entities[_entity] = EntityStatus::Enabled; 
    }

    void EntityProvider::disableEntity( const Entity& _entity )
    { 
        assert( m_entities[_entity] != EntityStatus::Unassigned );
        m_entities[_entity] = EntityStatus::Disabled; 
    }
    
    bool EntityProvider::isEntityEnabled( const Entity& _entity ) const
    { 
        assert( m_entities[_entity] != EntityStatus::Unassigned );
        return m_entities[_entity] == EntityStatus::Enabled; 
    }
}