#include "MultipleInputNodeBuilder.hpp"
#include "Nodes/MultipleInputOperators/MultipleInputOperationNode.hpp"
#include "BuilderStorage.hpp"
#include "UnaryNodeBuilder.hpp"
#include "BinaryNodeBuilder.hpp"
#include "PassThroughLayerNodeBuilder.hpp"
#include "VariableSingleValueNodeBuilder.hpp"
#include "VariableBufferNodeBuilder.hpp"
#include <algorithm>

MultipleInputNodeBuilder::MultipleInputNodeBuilder(BuilderStorage& builderStorage,
                                                   std::unique_ptr<IMultipleInputOperationNodesFactory<BNN_TYPE>> factory)
    : m_builderStorage(builderStorage)
    , m_factory(std::move(factory))
{
}

NotNull<UnaryNodeBuilder> MultipleInputNodeBuilder::addInput(UnaryNodeSpecs specs)
{
    auto l_builder = m_builderStorage.createUnaryNodeBuilder(std::move(specs.factory));
    m_inputBuilders.push_back(l_builder);
    m_operationBuilders.push_back(l_builder);
    return l_builder;
}

NotNull<BinaryNodeBuilder> MultipleInputNodeBuilder::addInput(BinaryNodeSpecs specs)
{
    auto l_builder = m_builderStorage.createBinaryNodeBuilder(std::move(specs.factory));
    m_inputBuilders.push_back(l_builder);
    m_operationBuilders.push_back(l_builder);
    return l_builder;
}

NotNull<VariableNodeBuilder> MultipleInputNodeBuilder::addInput(VariableNodeSpecs)
{
    auto l_builder = m_builderStorage.createVariableSingleValueNodeBuilder();
    m_inputBuilders.push_back(l_builder);
    return l_builder;
}

NotNull<ConstSingleValueNodeBuilder> MultipleInputNodeBuilder::addInput(ConstNodeSpecs)
{
    auto l_builder = m_builderStorage.createConstSingleValueNodeBuilder();
    m_inputBuilders.push_back(l_builder);
    return l_builder;
}

void MultipleInputNodeBuilder::addInput(NotNull<ConstSingleValueNodeBuilder> node)
{
    m_inputBuilders.push_back(node);
}

ArrayView<OperationNodeBuilder*> MultipleInputNodeBuilder::getOperations()
{
    return m_operationBuilders;
}

std::unique_ptr<OperationNode<BNN_TYPE>> MultipleInputNodeBuilder::build(BuilderToNodeMaps<BNN_TYPE> const& builderToNodeMaps)
{
    std::vector<NotNull<ComputationNode<BNN_TYPE>>> l_inputs;
    std::transform(std::begin(m_inputBuilders), std::end(m_inputBuilders), std::back_inserter(l_inputs),
                   [&](auto inputBuilder)
    {
        return builderToNodeMaps.getComputationNodeFromMaps(inputBuilder);
    });

    return m_factory->create(l_inputs);
}


