#include "LayeredNetworkBuilder.hpp"
#include "LayeredNetworkBuilders/FullyConnectedLayerSpecs.hpp"
#include "LayeredNetworkBuilders/FullyConnectedLayerBuilder.hpp"
#include "MultipleInputLayerNodeFactories/PassThrough.hpp"
#include "LayerNodeFactories/SigmoidLayer.hpp"

NotNull<FullyConnectedLayerBuilder> LayeredNetworkBuilder::setOutputLayer(FullyConnectedLayerSpecs const& specs)
{
    assert(specs.activation == "sigmoid");
    auto activationNode = m_networkBuilder.setRootNode(LayerNodeTag{}, std::make_unique<SigmoidLayerNodeFactory<BNN_TYPE>>(specs.numNeurons));
    auto layer = std::make_unique<FullyConnectedLayerBuilder>(activationNode, specs.numNeurons);
    auto specificLayer = layer.get();
    m_outputLayer = std::move(layer);
    return specificLayer;
}
