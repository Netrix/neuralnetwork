#pragma once
#include "IUnaryOperationNodesFactory.hpp"
#include "Nodes/UnaryOperations/SigmoidUnaryOperation.hpp"

template<class Type>
struct SigmoidNodeFactory : IUnaryOperationNodesFactory<Type>
{
    SigmoidNodeFactory(Type beta)
        : m_beta(beta)
    {
    }

    std::unique_ptr<UnaryOperationNode<Type> > create(NotNull<ComputationNode<Type>> input) override
    {
        return std::make_unique<SigmoidUnaryOperationNode<Type>>(input, m_beta);
    }

private:
    Type m_beta;
};
