//
//  Boundaries.h
//  Vertex2D
//
//  Created by Maximilian Maldacker on 01/09/2015.
//  Copyright (c) 2015 Maximilian Maldacker. All rights reserved.
//

#ifndef __Vertex2D__Boundaries__
#define __Vertex2D__Boundaries__

#include "Shapes.h"
#include "Size.h"
#include "Operator.h"
#include "LevelSet.h"

namespace Fluid
{

class Boundaries
{
public:
    Boundaries(Dimensions dimensions, int antialias);

    void RenderDirichlet(const std::vector<Renderer::Drawable*> & objects);
    void RenderNeumann(const std::vector<Renderer::Drawable*> & objects);
    void RenderBorders();
    void RenderVelocities(const std::vector<Renderer::Drawable*> & objects);
    void RenderLevelSet(LevelSet & levelSet);
    void RenderMask(Buffer & mask);

    auto GetWeights()
    {
        return mWeights(mNeumannBoundaries, mDirichletBoundaries);
    }
    
    auto GetDiagonals()
    {
        return mDiagonals(mNeumannBoundaries);
    }

    void Clear();

    friend class Engine;
//private:
    void Render(const std::vector<Renderer::Drawable*> & objects, const glm::mat4 & orth);

    Dimensions mDimensions;
    int mAntialias;
    
    Buffer mDirichletBoundaries;
    Buffer mNeumannBoundaries;
    Buffer mBoundariesVelocity;

    Operator mWeights;
    Operator mDiagonals;
    Operator mBoundaryMask;
    Operator mLevelSetMask;

    Renderer::Rectangle mHorizontal;
    Renderer::Rectangle mVertical;
};

}

#endif /* defined(__Vertex2D__Boundaries__) */
