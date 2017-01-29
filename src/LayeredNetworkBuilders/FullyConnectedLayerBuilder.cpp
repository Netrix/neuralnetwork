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

NotNull<FullyConnectedLayerBuilder> FullyConnectedLayerBuilder::setInputLayer(FullyConnectedLayerSpecs const& specs)
{
    assert(specs.activation == "sigmoid" or specs.activation == "relu");    // TODO replace it with proper factory

    LayerNodeBuilder* activationsLayer;

    if(specs.activation == "sigmoid")
    {
        activationsLayer = m_fullyConnectedLayer->setInput(LayerNodeSpecs{std::make_unique<SigmoidLayerNodeFactory<BNN_TYPE>>(specs.numNeurons)});
    }
    else if(specs.activation == "relu")
    {
        activationsLayer = m_fullyConnectedLayer->setInput(LayerNodeSpecs{std::make_unique<ReLULayerNodeFactory<BNN_TYPE>>(specs.numNeurons)});
    }
    else
    {
        throw 1;
    }

    auto layer = std::make_unique<FullyConnectedLayerBuilder>(activationsLayer, specs.numNeurons);
    auto specificLayer = layer.get();
    m_inputLayer = std::move(layer);
    return specificLayer;
}

void FullyConnectedLayerBuilder::setInputLayer(InputLayerSpecs const& specs)
{
    m_fullyConnectedLayer->setInput(ConstBufferNodeSpecs{specs.numInputs});
}
