//
//  LevelSet.h
//  Vortex2D
//

#ifndef LevelSet_h
#define LevelSet_h

#include <Vortex2D/Renderer/RenderTexture.h>
#include <Vortex2D/Renderer/Work.h>
#include <Vortex2D/Renderer/CommandBuffer.h>

namespace Vortex2D { namespace Fluid {

/**
 * @brief A signed distance field, which can be re-initialized. In other words, a level set.
 */
class LevelSet : public Renderer::RenderTexture
{
public:
    VORTEX2D_API LevelSet(const Renderer::Device& device, const glm::ivec2& size, int reinitializeIterations = 100);

    VORTEX2D_API void ExtrapolateBind(Renderer::Texture& solidPhi);

    VORTEX2D_API void Reinitialise();
    VORTEX2D_API void Extrapolate();
    void ExtrapolateRecord(vk::CommandBuffer commandBuffer);

private:
    Renderer::Texture mLevelSet0;
    Renderer::Texture mLevelSetBack;

    vk::UniqueSampler mSampler;

    Renderer::Work mExtrapolate;
    Renderer::Work::Bound mExtrapolateBound;
    Renderer::Work mRedistance;
    Renderer::Work::Bound mRedistanceFront;
    Renderer::Work::Bound mRedistanceBack;

    Renderer::CommandBuffer mExtrapolateCmd;
    Renderer::CommandBuffer mReinitialiseCmd;
};

}}

#endif
