//
//  GaussSeidel.h
//  Vortex2D
//

#ifndef Vortex2D_GaussSeidel_h
#define Vortex2D_GaussSeidel_h

#include <Vortex2D/Engine/LinearSolver/LinearSolver.h>
#include <Vortex2D/Engine/LinearSolver/Preconditioner.h>
#include <Vortex2D/Renderer/Work.h>
#include <Vortex2D/Renderer/CommandBuffer.h>

namespace Vortex2D { namespace Fluid {

/**
 * @brief An iterative black and red successive over relaxation linear solver.
 */
class GaussSeidel : public LinearSolver, public Preconditioner
{
public:
    GaussSeidel(const Renderer::Device& device, const glm::ivec2& size);

    void Init(Renderer::Buffer& A,
              Renderer::Buffer& b,
              Renderer::Buffer& pressure,
              Renderer::Work& buildMatrix,
              Renderer::Texture& solidPhi,
              Renderer::Texture& liquidPhi) override;

    /**
     * @brief Iterative solving of the linear equations in data
     */
    void Solve(Parameters& params) override;

    void Record(vk::CommandBuffer commandBuffer) override;

    void Record(vk::CommandBuffer commandBuffer, int iterations);
    void SetW(float w);

private:
    float mW;
    Renderer::Work mGaussSeidel;
    Renderer::Work::Bound mGaussSeidelBound;
    Renderer::CommandBuffer mGaussSeidelCmd;
    Renderer::CommandBuffer mInitCmd;
    Renderer::Buffer* mPressure;
};

}}

#endif
