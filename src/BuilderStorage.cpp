#include "BuilderStorage.hpp"

NotNull<BinaryNodeBuilder> BuilderStorage::createBinaryNodeBuilder(std::string const& operation)
{
    auto l_builder = std::make_unique<BinaryNodeBuilder>(*this, operation);
    operations.push_back(std::move(l_builder));
    return operations.back().get();
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
