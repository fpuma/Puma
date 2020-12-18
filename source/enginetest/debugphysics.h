#pragma once

#include <physics/debug/debugdraw.h>
#include <application/irenderer.h>
#include <application/commondefinitions.h>

using Vec2 = puma::physics::Vec2;
using RGBA = puma::physics::RGBA;

puma::app::Color colorTransform( const RGBA& color )
{
    return { (unsigned char)(color.r * 255.0f), (unsigned char)(color.g * 255.0f), (unsigned char)(color.b * 255.0f), (unsigned char)(color.a * 255.0f) };
}

class PhysicsTestDebugDraw : public puma::physics::DebugDraw
{
public:
    PhysicsTestDebugDraw( puma::app::IRenderer* _renderer )
    {
        m_renderer = _renderer;
    }

    void renderPolygon( const std::vector<Vec2>&& _vertices, const RGBA& _color ) override
    {
        std::vector<short> xCoords( _vertices.size() );
        std::vector<short> yCoords( _vertices.size() );

        std::transform( _vertices.begin(), _vertices.end(), xCoords.begin(), []( const Vec2& _vertex )
        {
            return (short)_vertex.x;
        } );

        std::transform( _vertices.begin(), _vertices.end(), yCoords.begin(), []( const Vec2& _vertex )
        {
            return (short)_vertex.y;
        } );

        m_renderer->renderPolygon( xCoords.data(), yCoords.data(), (int)_vertices.size(), colorTransform( _color ) );
    }

    void renderSolidPolygon( const std::vector<Vec2>&& _vertices, const RGBA& _color ) override
    {
        std::vector<short> xCoords( _vertices.size() );
        std::vector<short> yCoords( _vertices.size() );

        std::transform( _vertices.begin(), _vertices.end(), xCoords.begin(), []( const Vec2& _vertex )
        {
            return (short)_vertex.x;
        } );

        std::transform( _vertices.begin(), _vertices.end(), yCoords.begin(), []( const Vec2& _vertex )
        {
            return (short)_vertex.y;
        } );

        m_renderer->renderSolidPolygon( xCoords.data(), yCoords.data(), (int)_vertices.size(), colorTransform( _color ) );
    }

    void renderCircle( const Vec2&& _center, float _radius, const RGBA& _color ) override
    {
        m_renderer->renderCircle( (int)_center.x, (int)_center.y, (int)_radius, colorTransform( _color ) );
    }

    void renderSolidCircle( const Vec2&& _center, float _radius, const RGBA& _color ) override
    {
        m_renderer->renderSolidCircle( (int)_center.x, (int)_center.y, (int)_radius, colorTransform( _color ) );
    }

    void renderSegment( const Vec2&& _point1, const Vec2& _point2, const RGBA& _color ) override
    {
        m_renderer->renderSegment( (int)_point1.x, (int)_point1.y, (int)_point2.x, (int)_point2.y, colorTransform( _color ) );
    }

private:
    puma::app::IRenderer* m_renderer = nullptr;
};
