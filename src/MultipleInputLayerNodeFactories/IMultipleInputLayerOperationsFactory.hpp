#pragma once
#include "Nodes/OperationNode.hpp"
#include "Utils/NotNull.hpp"
#include <memory>
#include <vector>

template<class Type>
struct IMultipleInputLayerOperationsFactory
{
    virtual std::unique_ptr<OperationNode<Type>> create(std::vector<NotNull<ComputationNode<Type>>> const& inputs) = 0;

    virtual std::size_t getNumOutputs() const = 0;
};
