#pragma once
#include "NotNull.hpp"
#include "Nodes/UnaryOperations/UnaryOperationNode.hpp"
#include "Nodes/UnaryOperations/SigmoidUnaryOperation.hpp"
#include "Nodes/UnaryOperations/TanhUnaryOperation.hpp"
#include "Nodes/UnaryOperations/ReLUUnaryOperation.hpp"
#include "Nodes/UnaryOperations/PReLUUnaryOperation.hpp"

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
        else if(nodeType == "prelu")
        {
            return std::make_unique<PReLUUnaryOperationNode<Type>>(input);
        }
        assert(false);
        return nullptr; // TODO add implementation!!!
    }
};
