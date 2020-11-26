#pragma once

#include <engine/ecs/base/containers/isystemcontainer.h>

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

        void updateSystemsProperties() override;

    private:

        std::vector<ISystem*> m_systemsToUpdate;
        std::vector<ISystem*> m_systemsToUpdatePrePhysics;
        std::vector<ISystem*> m_systemsToUpdatePostPhysics;
    };
}