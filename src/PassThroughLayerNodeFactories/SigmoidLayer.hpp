#pragma once

#include "PassThroughLayerNodeFactories/IPassThroughLayerNodeFactory.hpp"
#include "Nodes/LayerNodes/SigmoidLayer.hpp"

template<class Type>
struct SigmoidLayerNodeFactory : IPassThroughLayerNodeFactory<Type>
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
