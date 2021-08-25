#include <precompiledengine.h>

#include "renderqueue.h"
#include "enginerendererhelpers.h"

namespace puma
{
    void RenderQueue::addRenderableTexture( AppTexture _texture, AppTextureSample _textureSample, RenderSize _renderSize, Position _position, RotationDegrees _rotation )
    {
        Rectangle frustum;
        float metersPerPixel;
        erh::getCameraInfo( frustum, metersPerPixel );

        RenderableTexture& renderable = m_textures[m_renderableTexturesCount];
        renderable.setTexture( _texture, _textureSample );
        renderable.setRotationDegrees( _rotation );

        Extent screenExtent;

        Rectangle boundingBox = erh::getAABB( _position, _renderSize );

        screenExtent.xPos = (s32)((boundingBox.lowerBoundary.x - frustum.lowerBoundary.x) / metersPerPixel);
        screenExtent.yPos = (s32)((frustum.upperBoundary.y - boundingBox.upperBoundary.y) / metersPerPixel);
        screenExtent.width = (s32)(_renderSize.x / metersPerPixel);
        screenExtent.height = (s32)(_renderSize.y / metersPerPixel);

        renderable.setScreenExtent( std::move( screenExtent ) );

        m_renderables.emplace_back( &renderable );

        ++m_renderableTexturesCount;
    }

    void RenderQueue::render()
    {
        for ( IRenderable* renderable : m_renderables )
        {
            renderable->render();
        }
    }

    void RenderQueue::clear()
    {
        m_renderables.clear();
        m_renderableTexturesCount = 0;
        m_renderableTextsCount = 0;
        m_renderableShapesCount = 0;
    }
}