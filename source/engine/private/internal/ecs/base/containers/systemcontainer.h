#pragma once

#include <engine/ecs/base/containers/isystemcontainer.h>
#include <utils/geometry/shapes/rectangle.h>

namespace puma
{
    class SystemContainer final : public ISystemContainer
    {
    public:

        void uninit();
        void prePhysicsUpdate( float _deltaTime );
        void update( float _deltaTime );
        void postPhysicsUpdate( float _deltaTime );

        void queueRenderables( QueueRenderableCallback _queueRenderableCallback );
        void queueDebugRenderables( QueueRenderableCallback _queueRenderableCallback );

        void updateSystemsProperties() override;

    protected:

        void onAdded( Key _key, ISystem* _system ) override;
        void onRemoved( Key _key, ISystem* _system ) override;

    private:

        std::vector<ISystem*> m_systemsToUpdate;
        std::vector<ISystem*> m_systemsToUpdatePrePhysics;
        std::vector<ISystem*> m_systemsToUpdatePostPhysics;
        std::vector<ISystem*> m_systemsToQueueRenderables;
        std::vector<ISystem*> m_systemsToQueueDebugRenderables;
    };
}