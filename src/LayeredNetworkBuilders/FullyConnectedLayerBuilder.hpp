#pragma once
#include "LayerBuilder.hpp"
#include "ArrayView.hpp"
#include "NotNull.hpp"
#include "LayerBuilder.hpp"
#include <vector>
#include <memory>

struct UnaryNodeBuilder;
struct ConstNodeBuilder;
struct LayerNodeBuilder;
struct MultipleInputNodeBuilder;
struct FullyConnectedLayerSpecs;
struct InputLayerSpecs;

struct FullyConnectedLayerBuilder : LayerBuilder
{
    FullyConnectedLayerBuilder(ArrayView<NotNull<UnaryNodeBuilder>> activations);

    NotNull<FullyConnectedLayerBuilder> setInputLayer(FullyConnectedLayerSpecs const& specs);

    void setInputLayer(InputLayerSpecs const& specs);

private:
    std::vector<NotNull<MultipleInputNodeBuilder>> m_addNodes;
    std::unique_ptr<LayerBuilder> m_inputLayer;
};
