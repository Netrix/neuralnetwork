#pragma once
#include "Nodes/OperationNode.hpp"
#include "Nodes/VariableNode.hpp"
#include "NotNull.hpp"
#include <memory>
#include <vector>

template<class Type>
struct ILayerOperationsFactory
{
    virtual std::unique_ptr<OperationNode<Type>> create(NotNull<ComputationNode<Type>> input,
                                                        NotNull<VariableNode<Type>> variables) = 0;

    virtual std::size_t getNumOutputs() const = 0;

    virtual std::size_t getNumVariables(std::size_t numInputs) const = 0;
};
