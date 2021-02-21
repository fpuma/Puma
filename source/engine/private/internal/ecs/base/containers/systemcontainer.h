#pragma once

#include <engine/ecs/base/containers/isystemcontainer.h>
#include <engine/resources/resourcedefs.h>

namespace puma
{
    class SystemContainer final : public ISystemContainer
    {
    public:

        void init();
        void uninit();
        void prePhysicsUpdate( float _deltaTime );
        void update( float _deltaTime );
        void postPhysicsUpdate( float _deltaTime );

        void queueRenderables( RenderablesBackInserter _renderablesBackInserter );
        void queueDebugRenderables( RenderablesBackInserter _renderablesBackInserter );

        void updateSystemsProperties() override;

    private:

        std::vector<ISystem*> m_systemsToUpdate;
        std::vector<ISystem*> m_systemsToUpdatePrePhysics;
        std::vector<ISystem*> m_systemsToUpdatePostPhysics;
        std::vector<ISystem*> m_systemsToQueueRenderables;
        std::vector<ISystem*> m_systemsToQueueDebugRenderables;
    };
}