#pragma once
#include <string>
#include <memory>
#include "IMultipleInputLayerOperationsFactory.hpp"
#include "ILayerOperationsFactory.hpp"
#include "NodeBuilders/NodeBuilder.hpp"

struct BinaryNodeSpecs
{
    std::string operation;
};

struct UnaryNodeSpecs
{
    std::string operation;
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
