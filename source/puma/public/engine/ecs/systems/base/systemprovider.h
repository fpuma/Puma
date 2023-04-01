#pragma once

#include <engine/ecs/systems/base/isystem.h>
#include <utils/containers/uniquerealizationcontainer.h>
#include <utils/numerictypes.h>

#include <assert.h>
#include <typeindex>
#include <unordered_map>
#include <vector>


namespace puma
{
    namespace pina
    {
        class ComponentProvider;
        class EntityProvider;
    }
    
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

    class SystemProvider final : private UniqueRealizationContainer<ISystem>
    {
    public:

        SystemProvider()
        {
            m_systemUpdates.insert( { SystemUpdateId::Update,{} } );
            m_systemUpdates.insert( { SystemUpdateId::PrePhysics,{} } );
            m_systemUpdates.insert( { SystemUpdateId::PostPhysics,{} } );
            m_systemUpdates.insert( { SystemUpdateId::QueueRenderables,{} } );
            m_systemUpdates.insert( { SystemUpdateId::CollisionStarted,{} } );
            m_systemUpdates.insert( { SystemUpdateId::CollisionStopped,{} } );
        }

        ~SystemProvider()
        {
#ifdef _DEBUG
            for (const auto& sysCfg : m_systemUpdates)
            {
                assert( sysCfg.second.empty() ); //Some systems have not unregistered all their updates
            }
#endif
        }

        template<class Interface, class Class>
        void registerSystemInterface() { registerInterface<Interface, Class>(); }

        template<class Class>
        void registerSystemClass() { registerClass<Class>(); }

        template<class T>
        std::shared_ptr<T> getSystemSafely() { return getSafely<T>(); }

        template<class T>
        std::shared_ptr<const T> getSystemSafely() const { return getSafely<T>(); }

        template<class T>
        T* getSystem() { return get<T>(); }
        
        template<class T>
        const T* getSystem() const { return get<T>(); }

        template<class T>
        bool containsSystem() const { return contains<T>(); }

        template<class T>
        void requestSystem()
        {
            SystemClassId sysTypeIndex = std::type_index( typeid(T) );
            if (contains<T>())
            {
                u32& count = m_systemRequestsCount.at( sysTypeIndex );
                ++count;
            }
            else
            {
                m_systemRequestsCount.insert( { std::type_index( typeid(T)), 1 } );
                add<T>();
            }
        }

        template<class T>
        void releaseSystem()
        {
            SystemClassId sysTypeIndex = std::type_index( typeid(T) );
            if (contains<T>())
            {
                u32& count = m_systemRequestsCount.at( sysTypeIndex );
                --count;
                if (0 == count)
                {
                    m_systemRequestsCount.erase( sysTypeIndex );
                    remove<T>();
                }
            }
        }

        template<class T>
        void subscribeSystemUpdate( SystemUpdateId _id, SystemPriority _priority = 5 )
        {
            assert( contains<T>() ); // The given system has not been registered
            assert( m_systemUpdates.contains( _id ) ); // The given system update ID has not been initialized

            if (!contains<T>()) return;
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
            assert( contains<T>() ); // The given system has not been registered
            assert( m_systemUpdates.contains( _id ) ); // The given system update ID has not been initialized

            if (!contains<T>()) return;
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

        void update( pina::EntityProvider& _entityProvider, pina::ComponentProvider& _componentProvider )
        {
            assert( m_systemUpdates.contains( SystemUpdateId::Update ) ); // The update vector has not been initialized

            auto& sysCfgList = m_systemUpdates.at( SystemUpdateId::Update );

            for (SystemConfig& sysCfg : sysCfgList)
            {
                ISystem* system = static_cast<ISystem*>(get( sysCfg.classId ));
                if (system->isEnabled())
                {
                    system->update( _entityProvider, _componentProvider );
                }
            }
        }

        void prePhysicsUpdate( pina::EntityProvider& _entityProvider, pina::ComponentProvider& _componentProvider )
        {
            assert( m_systemUpdates.contains( SystemUpdateId::PrePhysics ) ); // The update vector has not been initialized

            auto& sysCfgList = m_systemUpdates.at( SystemUpdateId::PrePhysics );

            for (SystemConfig& sysCfg : sysCfgList)
            {
                ISystem* system = static_cast<ISystem*>(get( sysCfg.classId ));
                if (system->isEnabled())
                {
                    system->prePhysicsUpdate( _entityProvider, _componentProvider );
                }
            }
        }

        void postPhysicsUpdate( pina::EntityProvider& _entityProvider, pina::ComponentProvider& _componentProvider )
        {
            assert( m_systemUpdates.contains( SystemUpdateId::PostPhysics ) ); // The update vector has not been initialized

            auto& sysCfgList = m_systemUpdates.at( SystemUpdateId::PostPhysics );

            for (SystemConfig& sysCfg : sysCfgList)
            {
                ISystem* system = static_cast<ISystem*>(get( sysCfg.classId ));
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
                ISystem* system = static_cast<ISystem*>(get( sysCfg.classId ));
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
                ISystem* system = static_cast<ISystem*>(get( sysCfg.classId ));
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
                ISystem* system = static_cast<ISystem*>(get( sysCfg.classId ));
                
                if (system->isEnabled())
                {
                    system->onCollisionStopped( _framePartPtrA, _framePartPtrB );
                }
            }
        }

    protected:

        void onAdded( std::shared_ptr<ISystem> _system, std::type_index _typeIndex ) override 
        {
            _system->onInit();
        }
        
        void onRemoved( std::shared_ptr<ISystem> _system, std::type_index _typeIndex ) override 
        {
            _system->onUninit();
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

        std::unordered_map <SystemClassId, u32> m_systemRequestsCount;
    };
}