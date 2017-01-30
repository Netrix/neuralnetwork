#pragma once
#include <string>
#include <memory>
#include "MultipleInputLayerNodeFactories/IMultipleInputLayerOperationsFactory.hpp"
#include "ConnectedLayerNodeFactories/IConnectedLayerNodeFactory.hpp"
#include "PassThroughLayerNodeFactories/IPassThroughLayerNodeFactory.hpp"
#include "UnaryOperationNodesFactories/IUnaryOperationNodesFactory.hpp"
#include "BinaryOperationNodesFactories/IBinaryOperationNodesFactory.hpp"
#include "MultipleInputOperationNodesFactories/IMultipleInputOperationNodesFactory.hpp"
#include "NodeBuilders/NodeBuilder.hpp"

struct BinaryNodeSpecs
{
    std::unique_ptr<IBinaryOperationNodesFactory<BNN_TYPE>> factory;
};

struct UnaryNodeSpecs
{
    std::unique_ptr<IUnaryOperationNodesFactory<BNN_TYPE>> factory;
};

struct MultipleInputNodeSpecs
{
    std::unique_ptr<IMultipleInputOperationNodesFactory<BNN_TYPE>> factory;
};

struct ConnectedLayerNodeSpecs
{
    std::unique_ptr<IConnectedLayerNodeFactory<BNN_TYPE>> factory;
    std::size_t numOutputs;
};

struct PassThroughLayerNodeSpecs
{
    std::unique_ptr<IPassThroughLayerNodeFactory<BNN_TYPE>> factory;
    std::size_t numOutputs;
};

struct MultipleInputLayerNodeSpecs
{
    std::unique_ptr<IMultipleInputLayerOperationsFactory<BNN_TYPE>> factory;
    std::size_t numOutputs;
};

struct VariableNodeSpecs
{
};

struct ConstNodeSpecs
{
};

struct ConstBufferNodeSpecs
{
    std::size_t numConsts;
};
