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

NotNull<VariableNodeBuilder> BuilderStorage::createVariableNodeBuilder()
{
    auto l_builder = std::make_unique<VariableNodeBuilder>();
    variables.push_back(std::move(l_builder));
    return variables.back().get();
}

NotNull<ConstNodeBuilder> BuilderStorage::createConstNodeBuilder()
{
    auto l_builder = std::make_unique<ConstNodeBuilder>();
    consts.push_back(std::move(l_builder));
    return consts.back().get();
}
