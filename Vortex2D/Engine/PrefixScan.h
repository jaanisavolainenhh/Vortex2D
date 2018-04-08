//
//  PrefixScan.h
//  Vortex2D
//

#ifndef Vortex2D_PrefixScan_h
#define Vortex2D_PrefixScan_h

#include <Vortex2D/Renderer/Work.h>
#include <Vortex2D/Renderer/CommandBuffer.h>

namespace Vortex2D { namespace Fluid {

class PrefixScan
{
public:
    class Bound
    {
    public:
        VORTEX2D_API void Record(vk::CommandBuffer commandBuffer);

        friend class PrefixScan;
    private:
        Bound(const std::vector<Renderer::CommandBuffer::CommandFn>& bufferBarriers,
              std::vector<Renderer::Work::Bound>&& bounds);

        std::vector<Renderer::CommandBuffer::CommandFn> mBufferBarriers;
        std::vector<Renderer::Work::Bound> mBounds;
    };

    VORTEX2D_API PrefixScan(const Renderer::Device& device, const glm::ivec2& size);

    VORTEX2D_API Bound Bind(Renderer::GenericBuffer& input, Renderer::GenericBuffer& output, Renderer::GenericBuffer& dispatchParams);

private:
    void BindRecursive(std::vector<Renderer::CommandBuffer::CommandFn>& bufferBarriers,
                       std::vector<Renderer::Work::Bound>& bound,
                       Renderer::GenericBuffer& input,
                       Renderer::GenericBuffer& output,
                       Renderer::GenericBuffer& dispatchParams,
                       Renderer::ComputeSize computeSize,
                       std::size_t level);

    int mSize;
    Renderer::Work mAddWork;
    Renderer::Work mPreScanWork;
    Renderer::Work mPreScanStoreSumWork;

    std::vector<Renderer::Buffer<int>> mPartialSums;
};

}}

#endif
