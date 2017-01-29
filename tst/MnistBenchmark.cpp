#include <gtest/gtest.h>
#include "MnistPreprocessedDataSet.hpp"
#include "LayeredNetworkBuilder.hpp"
#include "LayeredNetworkBuilders/FullyConnectedLayerSpecs.hpp"
#include "LayeredNetworkBuilders/FullyConnectedLayerBuilder.hpp"
#include "LayeredNetworkBuilders/InputLayerSpecs.hpp"
#include "NormalDistributionGenerator.hpp"
#include "LearnUtils.hpp"
#include <chrono>

// 240s -> 231s, errorSum: 48010.46
TEST(MnistBenchmark, SingleEpoch)
{
    std::string imagesPath = "../../../data/train-images-idx3-ubyte";
    std::string labelsPath = "../../../data/train-labels-idx1-ubyte";

    auto mnistDataset = MnistPreprocessedDataSet<float>(loadMnistDataset(imagesPath, labelsPath));
    std::cout << mnistDataset.getInputSampleSize() << " " << mnistDataset.getNumSamples() << " " << mnistDataset.getOutputSampleSize() << std::endl;

    LayeredNetworkBuilder LayeredNetworkBuilder;
    auto outLayer = LayeredNetworkBuilder.setOutputLayer(FullyConnectedLayerSpecs{mnistDataset.getOutputSampleSize(), "relu"});
    auto hiddenLayer = outLayer->setInputLayer(FullyConnectedLayerSpecs{32, "relu"});
    hiddenLayer->setInputLayer(InputLayerSpecs{mnistDataset.getInputSampleSize()});
    auto network = LayeredNetworkBuilder.buildBackPropagationNetwork(0.01f);

    network->setVariables(NormalDistributionGenerator<BNN_TYPE>(17, 0, 1e-1));

    using namespace std::chrono;
    auto start = steady_clock::now();

    auto errorSum = learnEpoch(network, mnistDataset, 512);

    auto end = steady_clock::now();

    std::cout << "Time taken: " << duration_cast<seconds>(end - start).count() << "s. errorSum: " << errorSum <<  std::endl;
}

// 236s -> 212s, errorSum: 48011.12
TEST(MnistBenchmark, SingleEpochParallel)
{
    std::string imagesPath = "../../../data/train-images-idx3-ubyte";
    std::string labelsPath = "../../../data/train-labels-idx1-ubyte";

    auto mnistDataset = MnistPreprocessedDataSet<float>(loadMnistDataset(imagesPath, labelsPath));
    std::cout << mnistDataset.getInputSampleSize() << " " << mnistDataset.getNumSamples() << " " << mnistDataset.getOutputSampleSize() << std::endl;

    LayeredNetworkBuilder layeredNetworkBuilder;
    auto outLayer = layeredNetworkBuilder.setOutputLayer(FullyConnectedLayerSpecs{mnistDataset.getOutputSampleSize(), "relu"});
    auto hiddenLayer = outLayer->setInputLayer(FullyConnectedLayerSpecs{32, "relu"});
    hiddenLayer->setInputLayer(InputLayerSpecs{mnistDataset.getInputSampleSize()});

    using namespace std::chrono;
    auto start = steady_clock::now();

    auto mainNetwork = layeredNetworkBuilder.buildBackPropagationNetwork(0.01f);
    mainNetwork->setVariables(NormalDistributionGenerator<BNN_TYPE>(17, 0, 1e-1));

    auto errorSum = learnEpochParallel(layeredNetworkBuilder, mainNetwork, mnistDataset, 512, 0.01f, 0);

    auto end = steady_clock::now();

    std::cout << "Time taken: " << duration_cast<seconds>(end - start).count() << "s. errorSum: " << errorSum <<  std::endl;
}

// TODO run all -> write time and error after single epoch, then reimplement LayeredNetworkBuilder with new layered nodes!!!

