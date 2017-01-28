#pragma once

#include "IMultipleInputLayerOperationsFactory.hpp"
#include "Nodes/MultipleInputLayerNodes/PassThroughMultipleInputLayerNode.hpp"

template<class Type>
struct PassThroughMultipleInputLayerNodeFactory : IMultipleInputLayerOperationsFactory<Type>
{
    PassThroughMultipleInputLayerNodeFactory(std::size_t numOutputs)
        : m_numOutputs(numOutputs)
    {}

    std::unique_ptr<OperationNode<Type>> create(std::vector<NotNull<ComputationNode<Type>>> const& inputs) override
    {
        assert(inputs.size() == m_numOutputs);
        return std::make_unique<PassThroughMultipleInputLayerNode<Type>>(inputs);
    }

    std::size_t getNumOutputs() const override
    {
        return m_numOutputs;
    }

private:
    std::size_t m_numOutputs;
};
