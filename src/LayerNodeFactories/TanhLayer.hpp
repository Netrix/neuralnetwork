#pragma once

#include "ILayerOperationsFactory.hpp"
#include "Nodes/LayerNodes/TanhLayer.hpp"

template<class Type>
struct TanhLayerNodeFactory : ILayerOperationsFactory<Type>
{
    TanhLayerNodeFactory(std::size_t beta)
        : m_beta(beta)
    {}

    std::unique_ptr<OperationNode<Type>> create(NotNull<ComputationNode<Type>> input,
                                                NotNull<VariableNode<Type>>,
                                                std::size_t) override   // TODO try to remove it?
    {
        return std::make_unique<TanhLayerNode<Type>>(input, m_beta);
    }

    std::size_t getNumVariables(std::size_t, std::size_t) const  override
    {
        return 0;
    }

private:
    std::size_t m_beta;
};
