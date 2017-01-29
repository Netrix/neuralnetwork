#pragma once
#include "IUnaryOperationNodesFactory.hpp"
#include "Nodes/UnaryOperations/PReLUUnaryOperation.hpp"

template<class Type>
struct PReLUNodeFactory : IUnaryOperationNodesFactory<Type>
{
    PReLUNodeFactory(Type beta=0.01)
        : m_beta(beta)
    {
    }

    std::unique_ptr<UnaryOperationNode<Type> > create(NotNull<ComputationNode<Type>> input) override
    {
        return std::make_unique<PReLUUnaryOperationNode<Type>>(input, m_beta);
    }

private:
    Type m_beta;
};
