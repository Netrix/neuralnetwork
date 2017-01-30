#pragma once

#include "MultipleInputOperationNodesFactories/IMultipleInputOperationNodesFactory.hpp"
#include "UnaryOperationNodesFactories/IUnaryOperationNodesFactory.hpp"
#include "BinaryOperationNodesFactories/IBinaryOperationNodesFactory.hpp"
#include "MultipleInputLayerNodeFactories/IMultipleInputLayerOperationsFactory.hpp"
#include "NodeSpecs.hpp"
#include "NodeBuilders/ConstNodeBuilder.hpp"
#include "NodeBuilders/VariableNodeBuilder.hpp"
#include "NodeBuilders/NodeBuilder.hpp"
#include "NodeBuilders/OperationNodeBuilder.hpp"
#include "Utils/NotNull.hpp"
#include <vector>
#include <memory>

struct MultipleInputNodeBuilder;
struct UnaryNodeBuilder;
struct BinaryNodeBuilder;
struct MultipleInputLayerNodeBuilder;
struct ConnectedLayerNodeBuilder;
struct PassThroughLayerNodeBuilder;
struct ConstSingleValueNodeBuilder;
struct ConstBufferNodeBuilder;
struct VariableSingleValueNodeBuilder;
struct VariableBufferNodeBuilder;

struct BuilderStorage
{
    NotNull<MultipleInputNodeBuilder> createMultipleInputNodeBuilder(std::unique_ptr<IMultipleInputOperationNodesFactory<BNN_TYPE>>);
    NotNull<UnaryNodeBuilder> createUnaryNodeBuilder(std::unique_ptr<IUnaryOperationNodesFactory<BNN_TYPE>>);
    NotNull<BinaryNodeBuilder> createBinaryNodeBuilder(std::unique_ptr<IBinaryOperationNodesFactory<BNN_TYPE>> factory);
    NotNull<MultipleInputLayerNodeBuilder> createMultipleInputLayerNodeBuilder(std::unique_ptr<IMultipleInputLayerOperationsFactory<BNN_TYPE>> factory);
    NotNull<ConnectedLayerNodeBuilder> createConnectedLayerNodeBuilder(ConnectedLayerNodeSpecs);
    NotNull<PassThroughLayerNodeBuilder> createPassThroughLayerNodeBuilder(PassThroughLayerNodeSpecs);
    NotNull<ConstSingleValueNodeBuilder> createConstSingleValueNodeBuilder();
    NotNull<ConstBufferNodeBuilder> createConstBufferNodeBuilder(std::size_t numConsts);
    NotNull<VariableSingleValueNodeBuilder> createVariableSingleValueNodeBuilder();
    NotNull<VariableBufferNodeBuilder> createVariableBufferNodeBuilder(std::size_t numVariables);

    std::size_t getNumConsts() const
    {
        return m_numConsts;
    }

    std::size_t getNumVariables() const
    {
        return m_numVariables;
    }

    auto const& getConstBuilders() const
    {
        return consts;
    }

    auto const& getVariableBuilders() const
    {
        return variables;
    }

private:
    std::size_t m_numConsts{};
    std::size_t m_numVariables{};
    std::vector<std::unique_ptr<ConstNodeBuilder>> consts;
    std::vector<std::unique_ptr<VariableNodeBuilder>> variables;
    std::vector<std::unique_ptr<OperationNodeBuilder>> operations; // should have generic operations later
};
