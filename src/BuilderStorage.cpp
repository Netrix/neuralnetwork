#include "BuilderStorage.hpp"
#include "NodeBuilders/NodeBuilder.hpp"
#include "NodeBuilders/BinaryNodeBuilder.hpp"
#include "NodeBuilders/UnaryNodeBuilder.hpp"
#include "NodeBuilders/ConstSingleValueNodeBuilder.hpp"
#include "NodeBuilders/ConstBufferNodeBuilder.hpp"
#include "NodeBuilders/MultipleInputNodeBuilder.hpp"
#include "NodeBuilders/MultipleInputLayerNodeBuilder.hpp"
#include "NodeBuilders/ConnectedLayerNodeBuilder.hpp"
#include "NodeBuilders/VariableSingleValueNodeBuilder.hpp"
#include "NodeBuilders/VariableBufferNodeBuilder.hpp"
#include "NodeBuilders/PassThroughLayerNodeBuilder.hpp"

NotNull<MultipleInputNodeBuilder> BuilderStorage::createMultipleInputNodeBuilder(std::unique_ptr<IMultipleInputOperationNodesFactory<BNN_TYPE>> factory)
{
    auto l_builder = std::make_unique<MultipleInputNodeBuilder>(*this, std::move(factory));
    auto l_builderPointer = l_builder.get();
    operations.push_back(std::move(l_builder));
    return l_builderPointer;
}

NotNull<UnaryNodeBuilder> BuilderStorage::createUnaryNodeBuilder(
        std::unique_ptr<IUnaryOperationNodesFactory<BNN_TYPE>> factory)
{
    auto l_builder = std::make_unique<UnaryNodeBuilder>(*this, std::move(factory));
    auto l_builderPointer = l_builder.get();
    operations.push_back(std::move(l_builder));
    return l_builderPointer;
}

NotNull<BinaryNodeBuilder> BuilderStorage::createBinaryNodeBuilder(std::unique_ptr<IBinaryOperationNodesFactory<BNN_TYPE>> factory)
{
    auto l_builder = std::make_unique<BinaryNodeBuilder>(*this, std::move(factory));
    auto l_builderPointer = l_builder.get();
    operations.push_back(std::move(l_builder));
    return l_builderPointer;
}

NotNull<MultipleInputLayerNodeBuilder> BuilderStorage::createMultipleInputLayerNodeBuilder(std::unique_ptr<IMultipleInputLayerOperationsFactory<BNN_TYPE>> factory)
{
    auto l_builder = std::make_unique<MultipleInputLayerNodeBuilder>(*this, std::move(factory));
    auto l_builderPointer = l_builder.get();
    operations.push_back(std::move(l_builder));
    return l_builderPointer;
}

NotNull<ConnectedLayerNodeBuilder> BuilderStorage::createConnectedLayerNodeBuilder(ConnectedLayerNodeSpecs layerNodeSpecs)
{
    auto l_builder = std::make_unique<ConnectedLayerNodeBuilder>(*this, std::move(layerNodeSpecs));
    auto l_builderPointer = l_builder.get();
    operations.push_back(std::move(l_builder));
    return l_builderPointer;
}

NotNull<PassThroughLayerNodeBuilder> BuilderStorage::createPassThroughLayerNodeBuilder(PassThroughLayerNodeSpecs layerNodeSpecs)
{
    auto l_builder = std::make_unique<PassThroughLayerNodeBuilder>(*this, std::move(layerNodeSpecs));
    auto l_builderPointer = l_builder.get();
    operations.push_back(std::move(l_builder));
    return l_builderPointer;
}


NotNull<VariableSingleValueNodeBuilder> BuilderStorage::createVariableSingleValueNodeBuilder()
{
    auto l_builder = std::make_unique<VariableSingleValueNodeBuilder>();
    auto l_builderPointer = l_builder.get();
    variables.push_back(std::move(l_builder));
    m_numVariables++;
    return l_builderPointer;
}

NotNull<ConstSingleValueNodeBuilder> BuilderStorage::createConstSingleValueNodeBuilder()
{
    auto l_builder = std::make_unique<ConstSingleValueNodeBuilder>();
    auto l_pointer = l_builder.get();
    consts.push_back(std::move(l_builder));
    m_numConsts++;
    return l_pointer;
}

NotNull<VariableBufferNodeBuilder> BuilderStorage::createVariableBufferNodeBuilder(std::size_t numVariables)
{
    auto l_builder = std::make_unique<VariableBufferNodeBuilder>(numVariables);
    auto l_pointer = l_builder.get();
    variables.push_back(std::move(l_builder));
    m_numVariables += numVariables;
    return l_pointer;
}

NotNull<ConstBufferNodeBuilder> BuilderStorage::createConstBufferNodeBuilder(std::size_t numConsts)
{
    auto l_builder = std::make_unique<ConstBufferNodeBuilder>(numConsts);
    auto l_pointer = l_builder.get();
    consts.push_back(std::move(l_builder));
    m_numConsts += numConsts;
    return l_pointer;
}
