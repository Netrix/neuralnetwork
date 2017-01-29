#pragma once
#include "IUnaryOperationNodesFactory.hpp"
#include "Nodes/UnaryOperations/ReLUUnaryOperation.hpp"

template<class Type>
struct ReLUNodeFactory : IUnaryOperationNodesFactory<Type>
{
    std::unique_ptr<UnaryOperationNode<Type> > create(NotNull<ComputationNode<Type>> input) override
    {
        return std::make_unique<ReLUUnaryOperationNode<Type>>(input);
    }
};
