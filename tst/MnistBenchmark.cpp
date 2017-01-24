#include <gtest/gtest.h>
#include "MnistPreprocessedDataSet.hpp"
#include "LayeredNetworkBuilder.hpp"
#include "LayeredNetworkBuilders/FullyConnectedLayerSpecs.hpp"
#include "LayeredNetworkBuilders/FullyConnectedLayerBuilder.hpp"
#include "LayeredNetworkBuilders/InputLayerSpecs.hpp"
#include "NormalDistributionGenerator.hpp"
#include "LearnUtils.hpp"
#include <chrono>


TEST(MnistBenchmark, DISABLED_SingleEpoch)
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

    auto errorSum = learnEpoch(network, mnistDataset, 256);

    auto end = steady_clock::now();

    std::cout << "Time taken: " << duration_cast<seconds>(end - start).count() << "ms. errorSum: " << errorSum <<  std::endl;
}

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
    auto network = layeredNetworkBuilder.buildBackPropagationNetwork(0.01f);

    network->setVariables(NormalDistributionGenerator<BNN_TYPE>(17, 0, 1e-1));

    using namespace std::chrono;
    auto start = steady_clock::now();

    auto errorSum = learnEpochParallel(layeredNetworkBuilder, mnistDataset, 256, 0.1f);

    auto end = steady_clock::now();

    std::cout << "Time taken: " << duration_cast<seconds>(end - start).count() << "ms. errorSum: " << errorSum <<  std::endl;
}

