#include <gtest/gtest.h>
#include "MnistPreprocessedDataSet.hpp"
#include "LayeredNetworkBuilder.hpp"
#include "LayeredNetworkBuilders/FullyConnectedLayerSpecs.hpp"
#include "LayeredNetworkBuilders/FullyConnectedLayerBuilder.hpp"
#include "LayeredNetworkBuilders/InputLayerSpecs.hpp"
#include "MultipleInputLayerNodeFactories/PassThrough.hpp"
#include "NormalDistributionGenerator.hpp"
#include "LearnUtils.hpp"
#include "LayerNodeFactories/SigmoidLayer.hpp"
#include "LayerNodeFactories/FullyConnectedLayer.hpp"
#include <chrono>

TEST(LayerNodeTests, ComparingOutputOfLayerNodeVsOldWay)
{
    // Reference network
    LayeredNetworkBuilder layeredNetworkBuilder;
    auto outLayer = layeredNetworkBuilder.setOutputLayer(FullyConnectedLayerSpecs{2, "sigmoid"});
    auto hiddenLayer = outLayer->setInputLayer(FullyConnectedLayerSpecs{2, "sigmoid"});
    hiddenLayer->setInputLayer(InputLayerSpecs{2});

    auto network = layeredNetworkBuilder.buildBackPropagationNetwork(0.01f);
    network->setVariables(NormalDistributionGenerator<BNN_TYPE>(17, 0, 1e-1));

    // New network
    NetworkBuilder networkBuilder;
    auto outActivationLayer = networkBuilder.setRootNode(LayerNodeTag{}, std::make_unique<SigmoidLayerNodeFactory<BNN_TYPE>>(2));
    auto outFullyConnected = outActivationLayer->setInput(LayerNodeTag{}, std::make_unique<FullyConnectedLayerNodeFactory<BNN_TYPE>>(2));
    auto hiddenActivationLayer = outFullyConnected->setInput(LayerNodeTag{}, std::make_unique<SigmoidLayerNodeFactory<BNN_TYPE>>(2));
    auto hiddenFullyConnected = hiddenActivationLayer->setInput(LayerNodeTag{}, std::make_unique<FullyConnectedLayerNodeFactory<BNN_TYPE>>(2));
    auto passThrough = hiddenFullyConnected->setInput(MultipleInputLayerNodeTag{}, std::make_unique<PassThroughMultipleInputLayerNodeFactory<BNN_TYPE>>(2)); // TODO replace it with const layer node
    passThrough->addInput(ConstTag{});
    passThrough->addInput(ConstTag{});

    auto newNetwork = networkBuilder.buildBackPropagationNetwork(0.01f);
    newNetwork->setVariables(network->getVariables());

    // Tests
    std::vector<BNN_TYPE> inputs = { 1.0, -1.0 };
    auto oldOutputs = network->forwardPass(inputs);
    auto newOutputs = newNetwork->forwardPass(inputs);
    std::cout << "old outputs: " << oldOutputs[0] << ", " << oldOutputs[1] << std::endl;
    std::cout << "new outputs: " << newOutputs[0] << ", " << newOutputs[1] << std::endl;

}
