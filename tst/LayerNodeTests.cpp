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

TEST(LayerNodeTests, ComparingOutputOfLayerNodeVsOldWayWithoutHiddenLayer)
{
    // Reference network
    LayeredNetworkBuilder layeredNetworkBuilder;
    auto outLayer = layeredNetworkBuilder.setOutputLayer(FullyConnectedLayerSpecs{2, "sigmoid"});
    outLayer->setInputLayer(InputLayerSpecs{2});

    auto network = layeredNetworkBuilder.buildBackPropagationNetwork(0.01f);
    network->setVariables(NormalDistributionGenerator<BNN_TYPE>(17, 0, 1e-1));

    // New network
    NetworkBuilder networkBuilder;
    auto outActivationLayer = networkBuilder.setRootNode(LayerNodeSpecs{std::make_unique<SigmoidLayerNodeFactory<BNN_TYPE>>(2)});
    auto outFullyConnected = outActivationLayer->setInput(LayerNodeSpecs{std::make_unique<FullyConnectedLayerNodeFactory<BNN_TYPE>>(2)});
    auto passThrough = outFullyConnected->setInput(MultipleInputLayerNodeSpecs{
                                                       std::make_unique<PassThroughMultipleInputLayerNodeFactory<BNN_TYPE>>(2)}); // TODO replace it with const layer node
    passThrough->addInput(ConstNodeSpecs{});
    passThrough->addInput(ConstNodeSpecs{});

    auto newNetwork = networkBuilder.buildBackPropagationNetwork(0.01f);
    newNetwork->setVariables(network->getVariables());


    // Tests
    std::vector<BNN_TYPE> inputs = { 1.0, -1.0 };
    auto oldOutputs = network->forwardPass(inputs);
    auto newOutputs = newNetwork->forwardPass(inputs);
    std::cout << "old outputs: " << oldOutputs[0] << ", " << oldOutputs[1] << std::endl;
    std::cout << "new outputs: " << newOutputs[0] << ", " << newOutputs[1] << std::endl;

    std::vector<BNN_TYPE> errors = { -1.0, 0.0 };
    network->backPropagate(errors);
    network->applyDeltaOnVariables();
    newNetwork->backPropagate(errors);
    newNetwork->applyDeltaOnVariables();

    std::cout << "Old  network weights" << std::endl;
    std::copy(std::begin(network->getVariables()), std::end(network->getVariables()), std::ostream_iterator<BNN_TYPE>(std::cout, ", "));
    std::cout << std::endl;

    std::cout << "New  network weights" << std::endl;
    std::copy(std::begin(newNetwork->getVariables()), std::end(newNetwork->getVariables()), std::ostream_iterator<BNN_TYPE>(std::cout, ", "));
    std::cout << std::endl;

    // After learning test
    oldOutputs = network->forwardPass(inputs);
    newOutputs = newNetwork->forwardPass(inputs);
    std::cout << "old outputs: " << oldOutputs[0] << ", " << oldOutputs[1] << std::endl;
    std::cout << "new outputs: " << newOutputs[0] << ", " << newOutputs[1] << std::endl;
}


TEST(LayerNodeTests, ComparingOutputOfLayerNodeVsOldWayWithHiddenLayer)
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
    auto outActivationLayer = networkBuilder.setRootNode(LayerNodeSpecs{std::make_unique<SigmoidLayerNodeFactory<BNN_TYPE>>(2)});
    auto outFullyConnected = outActivationLayer->setInput(LayerNodeSpecs{std::make_unique<FullyConnectedLayerNodeFactory<BNN_TYPE>>(2)});
    auto hiddenActivationLayer = outFullyConnected->setInput(LayerNodeSpecs{std::make_unique<SigmoidLayerNodeFactory<BNN_TYPE>>(2)});
    auto hiddenFullyConnected = hiddenActivationLayer->setInput(LayerNodeSpecs{std::make_unique<FullyConnectedLayerNodeFactory<BNN_TYPE>>(2)});
    auto passThrough = hiddenFullyConnected->setInput(MultipleInputLayerNodeSpecs{
                                                          std::make_unique<PassThroughMultipleInputLayerNodeFactory<BNN_TYPE>>(2)}); // TODO replace it with const layer node
    passThrough->addInput(ConstNodeSpecs{});
    passThrough->addInput(ConstNodeSpecs{});

    auto newNetwork = networkBuilder.buildBackPropagationNetwork(0.01f);
    newNetwork->setVariables(network->getVariables());


    // Tests
    std::vector<BNN_TYPE> inputs = { 1.0, -1.0 };
    auto oldOutputs = network->forwardPass(inputs);
    auto newOutputs = newNetwork->forwardPass(inputs);
    std::cout << "old outputs: " << oldOutputs[0] << ", " << oldOutputs[1] << std::endl;
    std::cout << "new outputs: " << newOutputs[0] << ", " << newOutputs[1] << std::endl;

    std::vector<BNN_TYPE> errors = { -1.0, 0.0 };
    network->backPropagate(errors);
    network->applyDeltaOnVariables();
    newNetwork->backPropagate(errors);
    newNetwork->applyDeltaOnVariables();

    std::cout << "Old  network weights" << std::endl;
    std::copy(std::begin(network->getVariables()), std::end(network->getVariables()), std::ostream_iterator<BNN_TYPE>(std::cout, ", "));
    std::cout << std::endl;

    std::cout << "New  network weights" << std::endl;
    std::copy(std::begin(newNetwork->getVariables()), std::end(newNetwork->getVariables()), std::ostream_iterator<BNN_TYPE>(std::cout, ", "));
    std::cout << std::endl;
}
