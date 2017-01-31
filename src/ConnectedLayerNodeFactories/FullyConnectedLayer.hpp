#pragma once

#include "IConnectedLayerNodeFactory.hpp"
#include "Nodes/LayerNodes/FullyConnectedLayer.hpp"
#include "Utils/Math.hpp"

template<class Type>
struct FullyConnectedLayerNodeFactory : IConnectedLayerNodeFactory<Type>
{
    std::unique_ptr<OperationNode<Type>> create(NotNull<ComputationNode<Type>> input,
                                                NotNull<VariableNode<Type>> variables,
                                                std::size_t numOutputs) override
    {
        if((input->getNumOutputs() % 8) == 0 and (numOutputs % 8) == 0)
        {
            return std::make_unique<FullyConnectedLayerNode<Type>>(input,
                                                                   variables,
                                                                   numOutputs,
                                                                   vectorMatrixMultiplyUnalignedFloat8);
        }
        else if((input->getNumOutputs() % 4) == 0 and (numOutputs % 4) == 0)
        {
            return std::make_unique<FullyConnectedLayerNode<Type>>(input,
                                                                   variables,
                                                                   numOutputs,
                                                                   vectorMatrixMultiplyUnalignedFloat4);
        }
        else
        {
            return std::make_unique<FullyConnectedLayerNode<Type>>(input,
                                                                   variables,
                                                                   numOutputs,
                                                                   vectorMatrixMultiplyFloat);
        }

    }

    std::size_t getNumVariables(std::size_t numInputs, std::size_t numOutputs) const  override
    {
        return numOutputs * (numInputs + 1);
    }
};
