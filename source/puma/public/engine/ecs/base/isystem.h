#pragma once

#include <engine/utils/position.h>
#include <engine/utils/renderdefinitions.h>

namespace puma
{

    using SystemPriority = u32;
    using SystemUpdateBitMask = u32;

    class IRenderQueue;

    enum SystemUpdateFlag : SystemUpdateBitMask
    {
        SystemUpdateFlag_Update = 0x1,
        SystemUpdateFlag_PrePhysicsUpdate = 0x2,
        SystemUpdateFlag_PostPhysicsUpdate = 0x4,
        SystemUpdateFlag_QueueRenderables = 0x08,
    };

    struct SystemProperties
    {
        SystemPriority priority = 5; //The lower the number the higher the priority
        SystemUpdateBitMask updateBitMask = 0; //Should be a combination of SystemUpdateFlags
    };

    class ISystem : public NonCopyable
    {
    public:

        virtual ~ISystem() {}

        virtual void uninit() = 0;
        virtual void update( float _deltaTime ) = 0;
        virtual void prePhysicsUpdate( float _deltaTime ) = 0;
        virtual void postPhysicsUpdate( float _deltaTime ) = 0;

        virtual void queueRenderables( IRenderQueue& _renderQueue ) = 0;

        virtual void setProperties( SystemProperties _properties ) = 0;
        virtual SystemProperties getProperties() const = 0;

    };
}