#pragma once
#include "LayerBuilder.hpp"
#include "Utils/ArrayView.hpp"
#include "Utils/NotNull.hpp"
#include "LayerBuilder.hpp"
#include "NodeBuilders/ConnectedLayerNodeBuilder.hpp"
#include <vector>
#include <memory>

struct UnaryNodeBuilder;
struct ConstSingleValueNodeBuilder;
struct MultipleInputLayerNodeBuilder;
struct MultipleInputNodeBuilder;
struct FullyConnectedLayerSpecs;
struct InputLayerSpecs;

struct FullyConnectedLayerBuilder : LayerBuilder
{
    FullyConnectedLayerBuilder(NotNull<PassThroughLayerNodeBuilder> activationLayer, std::size_t numOutputs);

    NotNull<FullyConnectedLayerBuilder> setInputLayer(FullyConnectedLayerSpecs specs);

    void setInputLayer(InputLayerSpecs const& specs);

private:
    ConnectedLayerNodeBuilder* m_fullyConnectedLayer;
    std::unique_ptr<LayerBuilder> m_inputLayer;
};
