#include "LayeredNetworkBuilder.hpp"
#include "LayeredNetworkBuilders/FullyConnectedLayerSpecs.hpp"
#include "LayeredNetworkBuilders/FullyConnectedLayerBuilder.hpp"
#include "MultipleInputLayerNodeFactories/PassThrough.hpp"
#include "LayerNodeFactories/SigmoidLayer.hpp"
#include "LayerNodeFactories/ReLULayer.hpp"

NotNull<FullyConnectedLayerBuilder> LayeredNetworkBuilder::setOutputLayer(FullyConnectedLayerSpecs const& specs)
{
    assert(specs.activation == "sigmoid");
    LayerNodeBuilder* activationsLayer;
    if(specs.activation == "sigmoid")   // TODO obviously change it to proper factory!
    {
        activationsLayer = m_networkBuilder.setRootNode(LayerNodeTag{}, std::make_unique<SigmoidLayerNodeFactory<BNN_TYPE>>(specs.numNeurons));
    }
    else if(specs.activation == "relu")
    {
        activationsLayer = m_networkBuilder.setRootNode(LayerNodeTag{}, std::make_unique<ReLULayerNodeFactory<BNN_TYPE>>(specs.numNeurons));
    }
    else
    {
        throw 1;
    }

    auto layer = std::make_unique<FullyConnectedLayerBuilder>(activationsLayer, specs.numNeurons);
    auto specificLayer = layer.get();
    m_outputLayer = std::move(layer);
    return specificLayer;
}
