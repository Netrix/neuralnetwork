#pragma once

#include "ILayerOperationsFactory.hpp"
#include "Nodes/LayerNodes/ReLULayer.hpp"

template<class Type>
struct ReLULayerNodeFactory : ILayerOperationsFactory<Type>
{
    ReLULayerNodeFactory(std::size_t numOutputs)
        : m_numOutputs(numOutputs)
    {}

    std::unique_ptr<OperationNode<Type>> create(NotNull<ComputationNode<Type>> input,
                                                NotNull<VariableNode<Type>> ) override
    {
        return std::make_unique<ReLULayerNode<Type>>(input);
    }

    std::size_t getNumOutputs() const override
    {
        return m_numOutputs;
    }

    std::size_t getNumVariables(std::size_t numInputs) const  override
    {
        return 0;
    }

private:
    std::size_t m_numOutputs;
};
