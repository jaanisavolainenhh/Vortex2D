//
//  Multigrid.h
//  Vertex2D
//
//  Created by Maximilian Maldacker on 10/09/2015.
//  Copyright (c) 2015 Maximilian Maldacker. All rights reserved.
//

#ifndef __Vertex2D__Multigrid__
#define __Vertex2D__Multigrid__

#include "LinearSolver.h"
#include "SuccessiveOverRelaxation.h"

namespace Fluid
{

class Multigrid : public LinearSolver
{
public:
    Multigrid(const glm::vec2 & size, int iterations = 5);

    void Init(LinearSolver::Data & data, Boundaries & boundaries) override;
    void Solve(LinearSolver::Data & data) override;

//private:
    int mDepths;

    std::vector<SuccessiveOverRelaxation> mXs;
    std::vector<LinearSolver::Data> mDatas;

    LinearSolver::Data * mDataPtr;
    LinearSolver::Data & GetData(int depth);

    Operator mCorrect;
    Operator mProlongate;
    Operator mResidual;
    Operator mRestrict;
};

}

#endif /* defined(__Vertex2D__Multigrid__) */
