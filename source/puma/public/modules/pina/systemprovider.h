#pragma once

#include <modules/pina/system.h>
#include <pina/private/systemprovider.h>

#include <memory>
#include <unordered_map>
#include <vector>


namespace puma
{
    class ComponentProvider;
    class EntityProvider;
    
    enum class SystemUpdateId
    {
        Update,
        PrePhysics,
        PostPhysics,
        QueueRenderables,
        CollisionStarted,
        CollisionStopped,
    };

    using SystemPriority = u32;

    class SystemProvider : public pina::SystemProvider
    {
    public:

        SystemProvider( pina::EcsData& _data )
            : pina::SystemProvider( _data )
        {
            m_systemUpdates.insert( { SystemUpdateId::Update,{} } );
            m_systemUpdates.insert( { SystemUpdateId::PrePhysics,{} } );
            m_systemUpdates.insert( { SystemUpdateId::PostPhysics,{} } );
            m_systemUpdates.insert( { SystemUpdateId::QueueRenderables,{} } );
            m_systemUpdates.insert( { SystemUpdateId::CollisionStarted,{} } );
            m_systemUpdates.insert( { SystemUpdateId::CollisionStopped,{} } );
        }

        template<class T>
        void subscribeSystemUpdate( SystemUpdateId _id, SystemPriority _priority = 5 )
        {
            assert( containsSystem<T>() ); // The given system has not been registered
            assert( m_systemUpdates.contains( _id ) ); // The given system update ID has not been initialized

            if (!containsSystem<T>()) return;
            if (!m_systemUpdates.contains( _id )) return;

            SystemClassId sysClassId = SystemClassId( typeid(T) );

            auto& sysCfgList = m_systemUpdates.at( _id );
            auto itSysCfg = std::find_if( sysCfgList.begin(), sysCfgList.end(), [&sysClassId]( auto sysCfg )
                {
                    return sysCfg.classId == sysClassId;
                } );

            if (itSysCfg != sysCfgList.end())
            {
                if (itSysCfg->priority != _priority)
                {
                    itSysCfg->priority = _priority;
                    std::sort( sysCfgList.begin(), sysCfgList.end() );
                }
            }
            else
            {
                SystemConfig sysCfg = { sysClassId, _priority };
                sysCfgList.push_back( sysCfg );
                std::sort( sysCfgList.begin(), sysCfgList.end() );
            }
        }

        template<class T>
        void unsubscribeSystemUpdate( SystemUpdateId _id )
        {
            assert( containsSystem<T>() ); // The given system has not been registered
            assert( m_systemUpdates.contains( _id ) ); // The given system update ID has not been initialized

            if (!containsSystem<T>()) return;
            if (!m_systemUpdates.contains( _id )) return;

            SystemClassId sysClassId = SystemClassId( typeid(T) );

            auto& sysCfgList = m_systemUpdates.at( _id );
            auto itSysCfg = std::find_if( sysCfgList.begin(), sysCfgList.end(), [&sysClassId]( auto sysCfg )
                {
                    return sysCfg.classId == sysClassId;
                } );

            assert( itSysCfg != sysCfgList.end() ); // The given system is not registered for the given update ID

            if (itSysCfg != sysCfgList.end())
            {
                sysCfgList.erase( itSysCfg );
            }
        }

        void update( EntityProvider& _entityProvider, ComponentProvider& _componentProvider )
        {
            assert( m_systemUpdates.contains( SystemUpdateId::Update ) ); // The update vector has not been initialized

            auto& sysCfgList = m_systemUpdates.at( SystemUpdateId::Update );

            for (SystemConfig& sysCfg : sysCfgList)
            {
                System* system = static_cast<System*>(getSystem( sysCfg.classId ));
                if (system->isEnabled())
                {
                    system->update( _entityProvider, _componentProvider );
                }
            }
        }

        void prePhysicsUpdate( EntityProvider& _entityProvider, ComponentProvider& _componentProvider )
        {
            assert( m_systemUpdates.contains( SystemUpdateId::PrePhysics ) ); // The update vector has not been initialized

            auto& sysCfgList = m_systemUpdates.at( SystemUpdateId::PrePhysics );

            for (SystemConfig& sysCfg : sysCfgList)
            {
                System* system = static_cast<System*>(getSystem( sysCfg.classId ));
                if (system->isEnabled())
                {
                    system->prePhysicsUpdate( _entityProvider, _componentProvider );
                }
            }
        }

        void postPhysicsUpdate( EntityProvider& _entityProvider, ComponentProvider& _componentProvider )
        {
            assert( m_systemUpdates.contains( SystemUpdateId::PostPhysics ) ); // The update vector has not been initialized

            auto& sysCfgList = m_systemUpdates.at( SystemUpdateId::PostPhysics );

            for (SystemConfig& sysCfg : sysCfgList)
            {
                System* system = static_cast<System*>(getSystem( sysCfg.classId ));
                if (system->isEnabled())
                {
                    system->postPhysicsUpdate( _entityProvider, _componentProvider );
                }
            }
        }
        
        void queueRenderables( IRenderQueue& _renderQueue )
        {
            assert( m_systemUpdates.contains( SystemUpdateId::QueueRenderables ) ); // The update vector has not been initialized

            auto& sysCfgList = m_systemUpdates.at( SystemUpdateId::QueueRenderables );

            for (SystemConfig& sysCfg : sysCfgList)
            {
                System* system = static_cast<System*>(getSystem( sysCfg.classId ));
                if (system->isEnabled())
                {
                    system->queueRenderables( _renderQueue );
                }
            }
        }

        void onCollisionStarted( leo::FramePartID _framePartPtrA, leo::FramePartID _framePartPtrB, leo::ContactPoint _contactPoint )
        {
            assert( m_systemUpdates.contains( SystemUpdateId::CollisionStarted ) ); // The update vector has not been initialized
            
            auto& sysCfgList = m_systemUpdates.at( SystemUpdateId::CollisionStarted );

            for (SystemConfig& sysCfg : sysCfgList)
            {
                System* system = static_cast<System*>(getSystem( sysCfg.classId ));
                if (system->isEnabled())
                {
                    system->onCollisionStarted( _framePartPtrA, _framePartPtrB, _contactPoint );
                }
            }
        }

        void onCollisionStopped( leo::FramePartID _framePartPtrA, leo::FramePartID _framePartPtrB )
        {
            assert( m_systemUpdates.contains( SystemUpdateId::CollisionStopped ) ); // The update vector has not been initialized

            auto& sysCfgList = m_systemUpdates.at( SystemUpdateId::CollisionStopped );

            for (SystemConfig& sysCfg : sysCfgList)
            {
                System* system = static_cast<System*>(getSystem( sysCfg.classId ));
                
                if (system->isEnabled())
                {
                    system->onCllisionStopped( _framePartPtrA, _framePartPtrB );
                }
            }
        }

    private:

        using SystemClassId = std::type_index;

        // This struct is to identify each system and its priority inside a specific update list.
        struct SystemConfig
        {
            SystemClassId classId;
            SystemPriority priority = 5; //The lower the number the higher the priority

            bool operator < ( const SystemConfig& _other ) const { return priority < _other.priority; }
        };

        std::unordered_map<SystemUpdateId, std::vector<SystemConfig>> m_systemUpdates;
    };
}