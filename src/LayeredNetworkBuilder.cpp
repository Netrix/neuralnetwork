#include "LayeredNetworkBuilder.hpp"
#include "LayeredNetworkBuilders/FullyConnectedLayerSpecs.hpp"
#include "LayeredNetworkBuilders/FullyConnectedLayerBuilder.hpp"
#include "MultipleInputLayerNodeFactories/PassThrough.hpp"
#include "LayerNodeFactories/SigmoidLayer.hpp"
#include "LayerNodeFactories/ReLULayer.hpp"

NotNull<FullyConnectedLayerBuilder> LayeredNetworkBuilder::setOutputLayer(FullyConnectedLayerSpecs specs)
{
    auto activationsLayer = m_networkBuilder.setRootNode(LayerNodeSpecs{std::move(specs.activationFactory), specs.numNeurons});
    auto layer = std::make_unique<FullyConnectedLayerBuilder>(activationsLayer, specs.numNeurons);
    auto specificLayer = layer.get();
    m_outputLayer = std::move(layer);
    return specificLayer;
}
