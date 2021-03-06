#pragma once
#include "Nodes/OperationNode.hpp"
#include "Nodes/VariableNode.hpp"
#include "Utils/NotNull.hpp"
#include <memory>
#include <vector>

template<class Type>
struct IConnectedLayerNodeFactory
{
    virtual std::unique_ptr<OperationNode<Type>> create(NotNull<ComputationNode<Type>> input,
                                                        NotNull<VariableNode<Type>> variables,
                                                        std::size_t numOutputs) = 0;

    virtual std::size_t getNumVariables(std::size_t numInputs, std::size_t numOutputs) const = 0;
};
