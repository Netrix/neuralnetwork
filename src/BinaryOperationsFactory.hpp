#pragma once
#include "NotNull.hpp"
#include "BinaryOperationNode.hpp"

struct BinaryOperationsFactory
{
    std::unique_ptr<BinaryOperationNode> create(std::string const& nodeType,
                                                NotNull<ComputationNode> firstInput,
                                                NotNull<ComputationNode> secondInput)
    {
        return nullptr; // TODO add implementation!!!
    }
};
