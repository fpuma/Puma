#include <precompiledengine.h>

#include <internal/ecs/base/containers/systemcontainer.h>

namespace puma
{

    void SystemContainer::onAdded( Key _key, ISystem* _system )
    {
        SystemProperties properties = _system->getProperties();

        auto sortCallback = []( const ISystem* _sys1, const ISystem* _sys2 )
        {
            return _sys1->getProperties().priority < _sys2->getProperties().priority;
        };

        if ( properties.updateBitMask & (SystemUpdateBitMask)SystemUpdateFlag::Update )
        {
            m_systemsToUpdate.push_back( _system );
            std::sort( m_systemsToUpdate.begin(), m_systemsToUpdate.end(), sortCallback );
        }

        if ( properties.updateBitMask & (SystemUpdateBitMask)SystemUpdateFlag::PrePhysicsUpdate )
        {
            m_systemsToUpdatePrePhysics.push_back( _system );
            std::sort( m_systemsToUpdatePrePhysics.begin(), m_systemsToUpdatePrePhysics.end(), sortCallback );
        }

        if ( properties.updateBitMask & (SystemUpdateBitMask)SystemUpdateFlag::PostPhysicsUpdate )
        {
            m_systemsToUpdatePostPhysics.push_back( _system );
            std::sort( m_systemsToUpdatePostPhysics.begin(), m_systemsToUpdatePostPhysics.end(), sortCallback );
        }

        if ( properties.updateBitMask & (SystemUpdateBitMask)SystemUpdateFlag::QueueRenderables )
        {
            m_systemsToQueueRenderables.push_back( _system );
        }

        if ( properties.updateBitMask & (SystemUpdateBitMask)SystemUpdateFlag::QueueDebugRenderables )
        {
            m_systemsToQueueDebugRenderables.push_back( _system );
        }
    }

    void SystemContainer::onRemoved( Key _key, ISystem* _system )
    {
        m_systemsToUpdate.erase( std::remove( m_systemsToUpdate.begin(), m_systemsToUpdate.end(), _system ), m_systemsToUpdate.end() );
        m_systemsToUpdatePrePhysics.erase( std::remove( m_systemsToUpdatePrePhysics.begin(), m_systemsToUpdatePrePhysics.end(), _system ), m_systemsToUpdatePrePhysics.end() );
        m_systemsToUpdatePostPhysics.erase( std::remove( m_systemsToUpdatePostPhysics.begin(), m_systemsToUpdatePostPhysics.end(), _system ), m_systemsToUpdatePostPhysics.end() );
    }

    void SystemContainer::uninit()
    {
        traverse( []( ISystem* _ptr ) 
        {
            _ptr->uninit();
        } );
        m_systemsToUpdate.clear();
        m_systemsToUpdatePrePhysics.clear();
        m_systemsToUpdatePostPhysics.clear();
        clear();
    }
    
    void SystemContainer::update( float _deltaTime )
    {
        for( ISystem* systemPtr : m_systemsToUpdate )
        {
            systemPtr->update( _deltaTime );
        }
    }

    void SystemContainer::prePhysicsUpdate( float _deltaTime )
    {
        for ( ISystem* systemPtr : m_systemsToUpdatePrePhysics )
        {
            systemPtr->prePhysicsUpdate( _deltaTime );
        }
    }

    void SystemContainer::postPhysicsUpdate( float _deltaTime )
    {
        for ( ISystem* systemPtr : m_systemsToUpdatePostPhysics )
        {
            systemPtr->postPhysicsUpdate( _deltaTime );
        }
    }

    void SystemContainer::queueRenderables( QueueRenderableCallback _queueRenderableCallback )
    {
        for ( ISystem* systemPtr : m_systemsToQueueRenderables )
        {
            systemPtr->queueRenderables( _queueRenderableCallback );
        }
    }
    
    void SystemContainer::queueDebugRenderables( QueueRenderableCallback _queueRenderableCallback )
    {
        for ( ISystem* systemPtr : m_systemsToQueueDebugRenderables )
        {
            systemPtr->queueRenderables( _queueRenderableCallback );
        }
    }

    void SystemContainer::updateSystemsProperties()
    {
        m_systemsToUpdate.clear();
        m_systemsToUpdatePrePhysics.clear();
        m_systemsToUpdatePostPhysics.clear();
        m_systemsToQueueRenderables.clear();
        m_systemsToQueueDebugRenderables.clear();

        traverse( [&]( ISystem* _system )
        {
            SystemProperties properties = _system->getProperties();

            if ( properties.updateBitMask & (SystemUpdateBitMask)SystemUpdateFlag::Update )
            {
                m_systemsToUpdate.push_back( _system );
            }

            if ( properties.updateBitMask & (SystemUpdateBitMask)SystemUpdateFlag::PrePhysicsUpdate )
            {
                m_systemsToUpdatePrePhysics.push_back( _system );
            }

            if ( properties.updateBitMask & (SystemUpdateBitMask)SystemUpdateFlag::PostPhysicsUpdate )
            {
                m_systemsToUpdatePostPhysics.push_back( _system );
            }

            if ( properties.updateBitMask & (SystemUpdateBitMask)SystemUpdateFlag::QueueRenderables )
            {
                m_systemsToQueueRenderables.push_back( _system );
            }

            if ( properties.updateBitMask & (SystemUpdateBitMask)SystemUpdateFlag::QueueDebugRenderables )
            {
                m_systemsToQueueDebugRenderables.push_back( _system );
            }
            
        } );

        auto sortCallback = []( const ISystem* _sys1, const ISystem* _sys2 )
        {
            return _sys1->getProperties().priority < _sys2->getProperties().priority;
        };

        std::sort( m_systemsToUpdate.begin(), m_systemsToUpdate.end(), sortCallback );
        std::sort( m_systemsToUpdatePrePhysics.begin(), m_systemsToUpdatePrePhysics.end(), sortCallback );
        std::sort( m_systemsToUpdatePostPhysics.begin(), m_systemsToUpdatePostPhysics.end(), sortCallback );
    }
}