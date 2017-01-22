#pragma once
#include "NotNull.hpp"
#include "Nodes/MultipleInputOperators/AddOperation.hpp"

template<class Type>
struct MultipleInputOperationsFactory
{
    std::unique_ptr<MultipleInputOperationNode<Type>> create(std::string const& nodeType,
                                                             std::vector<NotNull<ComputationNode<Type>>> const& inputs)
    {
        if(nodeType == "add")
        {
            return std::make_unique<AddOperationNode<Type>>(inputs);
        }
        assert(false);
        return nullptr; // TODO add implementation!!!
    }
};
