#include "LayeredNetworkBuilder.hpp"
#include "LayeredNetworkBuilders/FullyConnectedLayerSpecs.hpp"
#include "LayeredNetworkBuilders/FullyConnectedLayerBuilder.hpp"

NotNull<FullyConnectedLayerBuilder> LayeredNetworkBuilder::setOutputLayer(FullyConnectedLayerSpecs const& specs)
{
    assert(specs.numNeurons == 1);
    auto activation = m_networkBuilder.setRootNode(UnaryNodeTag{}, specs.activation);
    auto layer = std::make_unique<FullyConnectedLayerBuilder>(activation);    // TODO should be able to create many activations later
    auto specificLayer = layer.get();
    m_outputLayer = std::move(layer);
    return specificLayer;
}
