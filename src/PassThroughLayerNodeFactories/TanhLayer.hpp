#pragma once

#include "IPassThroughLayerOperationsFactory.hpp"
#include "Nodes/LayerNodes/TanhLayer.hpp"

template<class Type>
struct TanhLayerNodeFactory : IPassThroughLayerOperationsFactory<Type>
{
    TanhLayerNodeFactory(std::size_t beta)
        : m_beta(beta)
    {}

    std::unique_ptr<OperationNode<Type>> create(NotNull<ComputationNode<Type>> input) override
    {
        return std::make_unique<TanhLayerNode<Type>>(input, m_beta);
    }

private:
    std::size_t m_beta;
};
