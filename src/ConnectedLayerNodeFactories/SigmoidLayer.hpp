#pragma once

#include "IConnectedLayerOperationsFactory.hpp"
#include "Nodes/LayerNodes/SigmoidLayer.hpp"

template<class Type>
struct SigmoidLayerNodeFactory : IConnectedLayerOperationsFactory<Type>
{
    SigmoidLayerNodeFactory(std::size_t beta=1.0)
        : m_beta(beta)
    {}

    std::unique_ptr<OperationNode<Type>> create(NotNull<ComputationNode<Type>> input,
                                                NotNull<VariableNode<Type>>,
                                                std::size_t) override
    {
        return std::make_unique<SigmoidLayerNode<Type>>(input, m_beta);
    }

    std::size_t getNumVariables(std::size_t, std::size_t) const  override
    {
        return 0;
    }

private:
    std::size_t m_beta;
};
