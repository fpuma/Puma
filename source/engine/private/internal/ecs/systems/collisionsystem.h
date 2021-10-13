#pragma once

#include <engine/ecs/systems/icollisionsystem.h>

#include <physics/debug/debugdraw.h>

namespace puma
{
    class IRenderQueue;

    class CollisionSystem final : public ICollisionSystem
    {
    public:

        void init( Vec2 _gravity ) override;
        void uninit() override;

        void registerEntity( Entity _entity, physics::FrameInfo _frameInfo, physics::FrameType _frameType ) override;
        void unregisterEntity( Entity _entity ) override;

        void update( float _deltaTime ) override {}
        void prePhysicsUpdate( float _deltaTime ) override {}
        void postPhysicsUpdate( float _deltaTime ) override;
        void queueRenderables( IRenderQueue& _renderQueue ) override;

        void setProperties( SystemProperties _properties ) override { m_properties = _properties; }
        SystemProperties getProperties() const override { return m_properties; }

        void setGravity( Vec2 _gravity ) override;
        Vec2 getGravity() override;

        void setCollisionCompatibility( const physics::CollisionCompatibility& _collisionCompatibility ) override;

    private:

#ifdef _DEBUG
        bool entityComponentCheck( Entity _entity );
#endif
        std::set<Entity> m_entities;
        SystemProperties m_properties;
        physics::WorldID m_worldId = physics::kInvalidPhysicsID;

        struct PhysicsDebugShape
        {
            Shape shape;
            Color color;
            bool solid = false;
        };

        using PhysicsDebugShapeList = std::vector<PhysicsDebugShape>;

        class PhysicsDebugDraw final : public physics::DebugDraw
        {
        public:

            void renderPolygon( const std::vector<Vec2>&& _vertices, const physics::RGBA&& _color ) override;
            void renderSolidPolygon( const std::vector<Vec2>&& _vertices, const physics::RGBA&& _color ) override;
            void renderCircle( const Vec2&& _center, float _radius, const physics::RGBA&& _color ) override;
            void renderSolidCircle( const Vec2&& _center, float _radius, const physics::RGBA&& _color ) override;
            void renderSegment( const Vec2&& _point1, const Vec2&& _point2, const physics::RGBA&& _color ) override;

            PhysicsDebugShapeList* dbgShapesPtr = nullptr;
        };

        PhysicsDebugShapeList m_debugShapes;
    };
}