#pragma once

#include <engine/ecs/systems/icollisionsystem.h>

#include <leo/debug/debugdraw.h>

namespace puma
{
    class IRenderQueue;

    class CollisionSystem final : public ICollisionSystem
    {
    public:

        void onInit() override;
        void onUninit() override;

        void registerEntity( Entity _entity, leo::FrameInfo _frameInfo, leo::FrameType _frameType ) override;
        void unregisterEntity( Entity _entity ) override;

        void postPhysicsUpdate( EntityProvider& _entityProvider, ComponentProvider& _componentProvider ) override;
        void queueRenderables( IRenderQueue& _renderQueue ) override;

        void setGravity( Vec2 _gravity ) override;
        Vec2 getGravity() override;

        void setCollisionCompatibility( const leo::CollisionCompatibility& _collisionCompatibility ) override;
        void setCollisionListener( std::unique_ptr<leo::ICollisionListener>&& _collisionListener );
        
        void enableDebugDraw() override { m_debugDraw = true; }
        void disableDebugDraw() override { m_debugDraw = false; }

        const leo::UserCollisionData getUserCollisionData( leo::FramePartID _framePartId ) const override;

    private:

#ifdef _DEBUG
        bool entityComponentCheck( Entity _entity );
#endif
        std::set<Entity> m_entities;
        leo::WorldID m_worldId;

        struct PhysicsDebugShape
        {
            Shape shape;
            Color color;
            bool solid = false;
        };

        using PhysicsDebugShapeList = std::vector<PhysicsDebugShape>;

        class PhysicsDebugDraw final : public leo::DebugDraw
        {
        public:

            void renderPolygon( const std::vector<Vec2>&& _vertices, const leo::RGBA&& _color ) override;
            void renderSolidPolygon( const std::vector<Vec2>&& _vertices, const leo::RGBA&& _color ) override;
            void renderCircle( const Vec2&& _center, float _radius, const leo::RGBA&& _color ) override;
            void renderSolidCircle( const Vec2&& _center, float _radius, const leo::RGBA&& _color ) override;
            void renderSegment( const Vec2&& _point1, const Vec2&& _point2, const leo::RGBA&& _color ) override;

            PhysicsDebugShapeList* dbgShapesPtr = nullptr;
        };

        PhysicsDebugShapeList m_debugShapes;
        bool m_debugDraw = false;
    };
}