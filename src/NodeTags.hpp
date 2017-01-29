#pragma once
#include <string>
#include <memory>
#include "IMultipleInputLayerOperationsFactory.hpp"
#include "ILayerOperationsFactory.hpp"
#include "UnaryOperationNodesFactories/IUnaryOperationNodesFactory.hpp"
#include "BinaryOperationNodesFactories/IBinaryOperationNodesFactory.hpp"
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
    std::string operation;
};

struct LayerNodeSpecs
{
    std::unique_ptr<ILayerOperationsFactory<BNN_TYPE>> factory;
};

struct MultipleInputLayerNodeSpecs
{
    std::unique_ptr<IMultipleInputLayerOperationsFactory<BNN_TYPE>> factory;
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
