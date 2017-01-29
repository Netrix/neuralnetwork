#include "BuilderStorage.hpp"

NotNull<MultipleInputNodeBuilder> BuilderStorage::createMultipleInputNodeBuilder(std::string const& operation)
{
    auto l_builder = std::make_unique<MultipleInputNodeBuilder>(*this, operation);
    auto l_builderPointer = l_builder.get();
    operations.push_back(std::move(l_builder));
    return l_builderPointer;
}

NotNull<UnaryNodeBuilder> BuilderStorage::createUnaryNodeBuilder(std::string const& operation)
{
    auto l_builder = std::make_unique<UnaryNodeBuilder>(*this, operation);
    auto l_builderPointer = l_builder.get();
    operations.push_back(std::move(l_builder));
    return l_builderPointer;
}

NotNull<BinaryNodeBuilder> BuilderStorage::createBinaryNodeBuilder(std::string const& operation)
{
    auto l_builder = std::make_unique<BinaryNodeBuilder>(*this, operation);
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

NotNull<LayerNodeBuilder> BuilderStorage::createLayerNodeBuilder(std::unique_ptr<ILayerOperationsFactory<BNN_TYPE>> factory)
{
    auto l_builder = std::make_unique<LayerNodeBuilder>(*this, std::move(factory));
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
