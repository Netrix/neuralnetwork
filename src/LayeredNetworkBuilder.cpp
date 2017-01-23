#include "LayeredNetworkBuilder.hpp"
#include "LayeredNetworkBuilders/FullyConnectedLayerSpecs.hpp"
#include "LayeredNetworkBuilders/FullyConnectedLayerBuilder.hpp"
#include "LayerNodeFactories/PassThrough.hpp"

NotNull<FullyConnectedLayerBuilder> LayeredNetworkBuilder::setOutputLayer(FullyConnectedLayerSpecs const& specs)
{
    auto layerNode = m_networkBuilder.setRootNode(LayerNodeTag{}, std::make_unique<PassThroughLayerNodeFactory<BNN_TYPE>>());
    std::vector<NotNull<UnaryNodeBuilder>> activations;
    activations.reserve(specs.numNeurons);

    for(decltype(specs.numNeurons) i{}; i < specs.numNeurons; ++i)
    {
        activations.push_back(
                    layerNode->addInput(UnaryNodeTag{}, specs.activation));

    }

    auto layer = std::make_unique<FullyConnectedLayerBuilder>(activations);    // TODO should be able to create many activations later
    auto specificLayer = layer.get();
    m_outputLayer = std::move(layer);
    return specificLayer;
}
