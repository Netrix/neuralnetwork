#include "FullyConnectedLayerBuilder.hpp"
#include "FullyConnectedLayerSpecs.hpp"
#include "InputLayerSpecs.hpp"
#include "FullyConnectedLayerSpecs.hpp"
#include "NodeBuilders/UnaryNodeBuilder.hpp"
#include "NodeBuilders/BinaryNodeBuilder.hpp"
#include "LayerNodeFactories/FullyConnectedLayer.hpp"
#include "LayerNodeFactories/SigmoidLayer.hpp"
#include "LayerNodeFactories/ReLULayer.hpp"
#include "MultipleInputLayerNodeFactories/PassThrough.hpp"


FullyConnectedLayerBuilder::FullyConnectedLayerBuilder(NotNull<LayerNodeBuilder> activationLayer, std::size_t numOutputs)
{
    m_fullyConnectedLayer = activationLayer->setInput(LayerNodeSpecs{std::make_unique<FullyConnectedLayerNodeFactory<BNN_TYPE>>(numOutputs)});
}

NotNull<FullyConnectedLayerBuilder> FullyConnectedLayerBuilder::setInputLayer(FullyConnectedLayerSpecs specs)
{
    auto numNeurons = specs.activationFactory->getNumOutputs();
    auto activationsLayer = m_fullyConnectedLayer->setInput(LayerNodeSpecs{std::move(specs.activationFactory)});
    auto layer = std::make_unique<FullyConnectedLayerBuilder>(activationsLayer, numNeurons);
    auto specificLayer = layer.get();
    m_inputLayer = std::move(layer);
    return specificLayer;
}

void FullyConnectedLayerBuilder::setInputLayer(InputLayerSpecs const& specs)
{
    m_fullyConnectedLayer->setInput(ConstBufferNodeSpecs{specs.numInputs});
}
