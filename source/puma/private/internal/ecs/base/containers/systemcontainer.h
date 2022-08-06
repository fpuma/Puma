#pragma once

#include <engine/ecs/base/containers/isystemcontainer.h>

namespace puma
{

    class IRenderQueue;

    class SystemContainer final : public ISystemContainer
    {
    public:

        void uninit();
        void prePhysicsUpdate( float _deltaTime );
        void update( float _deltaTime );
        void postPhysicsUpdate( float _deltaTime );

        void queueRenderables( IRenderQueue& _renderQueue );

        void updateSystemsProperties() override;

    protected:

        void onAdded( std::shared_ptr<ISystem> _system ) override;
        void onRemoved( std::shared_ptr<ISystem> _system ) override;

    private:

        std::vector<ISystem*> m_systemsToUpdate;
        std::vector<ISystem*> m_systemsToUpdatePrePhysics;
        std::vector<ISystem*> m_systemsToUpdatePostPhysics;
        std::vector<ISystem*> m_systemsToQueueRenderables;
    };
}