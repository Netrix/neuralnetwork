#pragma once

#include "ComputationNode.hpp"

template<class Type>
struct ConstNode : ComputationNode<Type>
{
    void backPropagate(ArrayView<Type const>) override
    {
    }

    void backPropagationPass() override
    {
    }
};
