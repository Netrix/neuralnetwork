#include <iostream>
#include <vector>
#include <memory>
#include <cassert>
#include <random>
#include <iomanip>
#include "NotNull.hpp"
#include "NodeTags.hpp"
#include "NodeBuilders/NodeBuilder.hpp"
#include "NodeBuilders/BinaryNodeBuilder.hpp"
#include "BuilderStorage.hpp"
#include "NetworkBuilder.hpp"
#include "LayeredNetworkBuilder.hpp"
#include "LayeredNetworkBuilders/FullyConnectedLayerSpecs.hpp"
#include "LayeredNetworkBuilders/FullyConnectedLayerBuilder.hpp"
#include "LayeredNetworkBuilders/InputLayerSpecs.hpp"
#include "MathVectorAdapter.hpp"
#include "StreamOperators.hpp"
#include "Datasets/MnistLoader.hpp"
#include <set>
#include "NormalDistributionGenerator.hpp"
#include "MnistPreprocessedDataSet.hpp"
#include "LearnUtils.hpp"

int main()
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


    for(int i = 0; i < 500; ++i)
    {
        auto errorSum = learnEpoch(network, mnistDataset, 256);
        std::cout << "epoch: " << i << " errorSum: " << errorSum <<  std::endl;

    }

    // TODO
    // 2. abstract initialization of weightsl
    // 3. multiple output layer (sigmoid, tanh, relu)
    // 4. abstract backprop
    //
    // zero-centering data! mean centering

    // im2col for convolution
}
