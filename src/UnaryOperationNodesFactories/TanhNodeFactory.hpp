#pragma once
#include "IUnaryOperationNodesFactory.hpp"
#include "Nodes/UnaryOperations/TanhUnaryOperation.hpp"

template<class Type>
struct TanhNodeFactory : IUnaryOperationNodesFactory<Type>
{
    TanhNodeFactory(Type beta)
        : m_beta(beta)
    {
    }

    std::unique_ptr<UnaryOperationNode<Type> > create(NotNull<ComputationNode<Type>> input) override
    {
        return std::make_unique<TanhUnaryOperationNode<Type>>(input, m_beta);
    }

private:
    Type m_beta;
};
