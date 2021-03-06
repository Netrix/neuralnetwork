#include "FullyConnectedLayerBuilder.hpp"
#include "FullyConnectedLayerSpecs.hpp"
#include "InputLayerSpecs.hpp"
#include "ConnectedLayerNodeFactories/FullyConnectedLayer.hpp"
#include "NodeBuilders/PassThroughLayerNodeBuilder.hpp"


FullyConnectedLayerBuilder::FullyConnectedLayerBuilder(NotNull<PassThroughLayerNodeBuilder> activationLayer, std::size_t numOutputs) // todo remove second parameter
{
    m_fullyConnectedLayer = activationLayer->setInput(ConnectedLayerNodeSpecs{std::make_unique<FullyConnectedLayerNodeFactory<BNN_TYPE>>(), numOutputs});
}

NotNull<FullyConnectedLayerBuilder> FullyConnectedLayerBuilder::setInputLayer(FullyConnectedLayerSpecs specs)
{
    auto activationsLayer = m_fullyConnectedLayer->setInput(PassThroughLayerNodeSpecs{std::move(specs.activationFactory), specs.numNeurons});
    auto layer = std::make_unique<FullyConnectedLayerBuilder>(activationsLayer, specs.numNeurons);
    auto specificLayer = layer.get();
    m_inputLayer = std::move(layer);
    return specificLayer;
}

void FullyConnectedLayerBuilder::setInputLayer(InputLayerSpecs const& specs)
{
    m_fullyConnectedLayer->setInput(ConstBufferNodeSpecs{specs.numInputs});
}
