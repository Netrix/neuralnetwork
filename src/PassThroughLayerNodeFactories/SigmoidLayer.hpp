#pragma once

#include "IPassThroughLayerOperationsFactory.hpp"
#include "Nodes/LayerNodes/SigmoidLayer.hpp"

template<class Type>
struct SigmoidLayerNodeFactory : IPassThroughLayerOperationsFactory<Type>
{
    SigmoidLayerNodeFactory(std::size_t beta=1.0)
        : m_beta(beta)
    {}

    std::unique_ptr<OperationNode<Type>> create(NotNull<ComputationNode<Type>> input) override
    {
        return std::make_unique<SigmoidLayerNode<Type>>(input, m_beta);
    }

private:
    std::size_t m_beta;
};
