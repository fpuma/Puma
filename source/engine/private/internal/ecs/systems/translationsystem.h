#pragma once
#include <engine/ecs/base/entity.h>
#include <engine/ecs/base/isystem.h>

namespace puma
{

    class ComponentProvider;

    class TranslationSystem final : public ISystem
    {
    public:

        void uninit() {}
        void update( float _deltaTime ) {}
        void prePhysicsUpdate( float _deltaTime ) override {}
        void postPhysicsUpdate( float _deltaTime ) override {}

        void setProperties( SystemProperties _properties ) override { m_properties = _properties; }
        SystemProperties getProperties() const { return m_properties; }


        void internalUninit() {};
        void internalUpdate( ComponentProvider* _componentProvider, Entity _entity, float _deltaTime );
#ifdef _DEBUG
        bool entityComponentCheck( Entity _entity );
#endif

    private:

        SystemProperties m_properties;
    };
}