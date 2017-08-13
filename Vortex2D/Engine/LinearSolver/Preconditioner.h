//
//  Preconditioner.h
//  Vortex2D
//

#ifndef Vortex2D_Preconditioner_h
#define Vortex2D_Preconditioner_h

#include <Vortex2D/Renderer/Buffer.h>
#include <Vortex2D/Renderer/Texture.h>
#include <Vortex2D/Renderer/Work.h>

namespace Vortex2D { namespace Fluid {

/**
 * @brief An interface to represent a linear solver preconditioner.
 */
struct Preconditioner
{
    virtual ~Preconditioner() {}

    virtual void Init(Renderer::Buffer& A,
                      Renderer::Buffer& b,
                      Renderer::Buffer& x,
                      Renderer::Work& buildMatrix,
                      Renderer::Texture& solidPhi,
                      Renderer::Texture& liquidPhi) = 0;

    virtual void Record(vk::CommandBuffer ) = 0;
};

}}

#endif
