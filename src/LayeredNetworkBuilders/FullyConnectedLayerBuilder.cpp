#include "FullyConnectedLayerBuilder.hpp"
#include "FullyConnectedLayerSpecs.hpp"
#include "InputLayerSpecs.hpp"
#include "FullyConnectedLayerSpecs.hpp"
#include "NodeBuilders/UnaryNodeBuilder.hpp"
#include "NodeBuilders/BinaryNodeBuilder.hpp"
#include "LayerNodeFactories/FullyConnectedLayer.hpp"
#include "LayerNodeFactories/SigmoidLayer.hpp"
#include "MultipleInputLayerNodeFactories/PassThrough.hpp"

namespace
{

std::vector<NotNull<UnaryNodeBuilder>> createFirstNeuronInputs(FullyConnectedLayerSpecs const& specs,
                                                               NotNull<MultipleInputNodeBuilder> neuronAddNode)
{
    std::vector<NotNull<UnaryNodeBuilder>> activations;
    activations.reserve(specs.numNeurons);

    neuronAddNode->addInput(VariableTag{}); // w0
    for(decltype(specs.numNeurons) i = 0; i < specs.numNeurons; ++i)
    {
        auto mul = neuronAddNode->addInput(BinaryNodeTag{}, "mul");
        activations.push_back(mul->setFirstInput(UnaryNodeTag{}, specs.activation));
        mul->setSecondInput(VariableTag{});
    }
    return activations;
}

template<class BuilderType>
void createOtherNeuron(NotNull<MultipleInputNodeBuilder> neuronAddNode,
                       std::vector<NotNull<BuilderType>> & inputs)
{
    auto numNeurons = inputs.size();
    neuronAddNode->addInput(VariableTag{}); // w0
    for(decltype(numNeurons) i = 0; i < numNeurons; ++i)
    {
        auto mul = neuronAddNode->addInput(BinaryNodeTag{}, "mul");
        mul->setFirstInput(inputs[i]);
        mul->setSecondInput(VariableTag{});
    }
}

std::vector<NotNull<ConstNodeBuilder>> createFirstNeuronInputs(std::size_t numInputs,
                                                               NotNull<MultipleInputNodeBuilder> neuronAddNode)
{
    std::vector<NotNull<ConstNodeBuilder>> inputs;
    inputs.reserve(numInputs);

    neuronAddNode->addInput(VariableTag{}); // w0
    for(decltype(numInputs) i = 0; i < numInputs; ++i)
    {
        auto mul = neuronAddNode->addInput(BinaryNodeTag{}, "mul");
        inputs.push_back(mul->setFirstInput(ConstTag{}));
        mul->setSecondInput(VariableTag{});
    }
    return inputs;
}

} // namespace

FullyConnectedLayerBuilder::FullyConnectedLayerBuilder(NotNull<LayerNodeBuilder> activationLayer, std::size_t numOutputs)
{
    m_fullyConnectedLayer = activationLayer->setInput(LayerNodeTag{}, std::make_unique<FullyConnectedLayerNodeFactory<BNN_TYPE>>(numOutputs));
}

//FullyConnectedLayerBuilder::FullyConnectedLayerBuilder(ArrayView<NotNull<UnaryNodeBuilder>> activations)
//{
//    m_addNodes.reserve(activations.size());
//    for(auto act : activations)
//    {
//        m_addNodes.push_back(act->setInput(MultipleInputTag{}, "add"));
//    }
//}

NotNull<FullyConnectedLayerBuilder> FullyConnectedLayerBuilder::setInputLayer(FullyConnectedLayerSpecs const& specs)
{
    assert(specs.activation == "sigmoid");

    auto activationsLayer = m_fullyConnectedLayer->setInput(LayerNodeTag{}, std::make_unique<SigmoidLayerNodeFactory<BNN_TYPE>>(specs.numNeurons));

//    auto inputActivations = createFirstNeuronInputs(specs, m_addNodes.front());
//    auto numNeurons = m_addNodes.size();
//    for(decltype(numNeurons) i = 1; i < numNeurons; ++i)
//    {
//        createOtherNeuron(m_addNodes[i], inputActivations);
//    }

    auto layer = std::make_unique<FullyConnectedLayerBuilder>(activationsLayer, specs.numNeurons);
    auto specificLayer = layer.get();
    m_inputLayer = std::move(layer);
    return specificLayer;
}

void FullyConnectedLayerBuilder::setInputLayer(InputLayerSpecs const& specs)
{
    auto passThrough = m_fullyConnectedLayer->setInput(MultipleInputLayerNodeTag{}, std::make_unique<PassThroughMultipleInputLayerNodeFactory<BNN_TYPE>>(specs.numInputs)); // TODO replace it with const layer node
//    passThrough->addInput(ConstTag{});
//    passThrough->addInput(ConstTag{});

//    auto inputs = createFirstNeuronInputs(specs.numInputs, m_addNodes.front());
    for(decltype(specs.numInputs) i = 0; i < specs.numInputs; ++i)
    {
        passThrough->addInput(ConstTag{});
//        createOtherNeuron(m_addNodes[i], inputs);
    }
}
