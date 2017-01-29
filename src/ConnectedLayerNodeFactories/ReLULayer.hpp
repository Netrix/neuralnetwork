#pragma once

#include "IConnectedLayerOperationsFactory.hpp"
#include "Nodes/LayerNodes/ReLULayer.hpp"

template<class Type>
struct ReLULayerNodeFactory : IConnectedLayerOperationsFactory<Type>
{
    std::unique_ptr<OperationNode<Type>> create(NotNull<ComputationNode<Type>> input,
                                                NotNull<VariableNode<Type>>,
                                                std::size_t) override
    {
        return std::make_unique<ReLULayerNode<Type>>(input);
    }

    std::size_t getNumVariables(std::size_t, std::size_t) const  override
    {
        return 0;
    }
};
