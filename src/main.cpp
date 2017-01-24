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


int main()
{
    std::string imagesPath = "../../../data/train-images-idx3-ubyte";
    std::string labelsPath = "../../../data/train-labels-idx1-ubyte";

    auto mnistDataset = loadMnistDataset(imagesPath, labelsPath);
    std::cout << mnistDataset.imageWidth << " " << mnistDataset.imageHeight << " " << mnistDataset.imageData.size() << " " << mnistDataset.labels.size() << " " << (int)mnistDataset.labels[0] << std::endl;

    std::set<int> labelsSet(std::begin(mnistDataset.labels), std::end(mnistDataset.labels));

    for(auto s : labelsSet)
    {
        std::cout << s << " ";
    }

    LayeredNetworkBuilder LayeredNetworkBuilder;
    auto outLayer = LayeredNetworkBuilder.setOutputLayer(FullyConnectedLayerSpecs{10, "tanh"});
    auto hiddenLayer = outLayer->setInputLayer(FullyConnectedLayerSpecs{32, "tanh"});
    hiddenLayer->setInputLayer(InputLayerSpecs{mnistDataset.imageHeight * mnistDataset.imageWidth});
    auto network = LayeredNetworkBuilder.buildBackPropagationNetwork();
    network->setLearningRate(0.01f);

    network->setVariables(NormalDistributionGenerator<BNN_TYPE>(17, 0, 1e-1));


    //TODO to ponizej ubrac w klase
//    for(int i = 0; i < 500; ++i)
//    {
//        BNN_TYPE errorSum = 0;
//        for(auto const& trainEntity : TRAIN_DATA)
//        {
//            auto result = make_math_adapter(network->forwardPass(trainEntity.input));
//            std::cout << std::fixed << std::setprecision(2) << "Input: " << trainEntity.input << ", expected result: " <<trainEntity.output << ", result: " << result << std::endl;
//            auto expected = make_math_adapter(trainEntity.output);
//            auto error = expected - result;
//            network->backPropagate(error);

//            auto squaredError = error * error;
//            errorSum += squaredError.sum();
//        }
//        network->applyDeltaOnVariables();
//        std::cout << "errorSum: " << errorSum <<  std::endl;
//    }

    // TODO
    // 2. abstract initialization of weightsl
    // 3. multiple output layer (sigmoid, tanh, relu)
    // 4. abstract backprop
    //
    // zero-centering data! mean centering

    // im2col for convolution
}
