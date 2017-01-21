#pragma once
#include "NotNull.hpp"
#include "UnaryOperations/UnaryOperationNode.hpp"
#include "UnaryOperations/SigmoidUnaryOperation.hpp"
#include "UnaryOperations/TanhUnaryOperation.hpp"
#include "UnaryOperations/ReLUUnaryOperation.hpp"

template<class Type>
struct UnaryOperationsFactory
{
    std::unique_ptr<UnaryOperationNode<Type>> create(std::string const& nodeType, NotNull<ComputationNode<Type>> input)
    {
        if(nodeType == "sigmoid")
        {
            return std::make_unique<SigmoidUnaryOperationNode<Type>>(input);
        }
        else if(nodeType == "tanh")
        {
            return std::make_unique<TanhUnaryOperationNode<Type>>(input);
        }
        else if(nodeType == "relu")
        {
            return std::make_unique<ReLUUnaryOperationNode<Type>>(input);
        }
        assert(false);
        return nullptr; // TODO add implementation!!!
    }
};
