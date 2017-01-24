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

template<class Type>
struct MnistPreprocessedDataSet
{
    MnistPreprocessedDataSet(MnistDataset const& mnistData)
        : m_inputSampleSize(mnistData.imageWidth * mnistData.imageHeight)
        , m_inputData(mnistData.imageData.size())
        , m_outputData(m_outputSampleSize * mnistData.labels.size())
    {
        std::transform(std::begin(mnistData.imageData), std::end(mnistData.imageData), std::begin(m_inputData),
                       [](auto v)
        {
            return (static_cast<Type>(v) / 255.0) - 0.5;
        });

        for(std::size_t i = 0, v = 0; i < m_outputData.size(); ++v)
        {
            for(std::size_t k = 0; k < 10; ++k, ++i)
            {
                m_outputData[i] = mnistData.labels[v] == k ? 1.0 : 0.0;
            }
        }
    }

    auto getInputSampleSize() const
    {
        return m_inputSampleSize;
    }

    auto getOutputSampleSize() const
    {
        return m_outputSampleSize;
    }

    auto getInputSample(std::size_t sampleIndex) const
    {
        return ArrayView<Type const>(m_inputData.data() + m_inputSampleSize * sampleIndex, m_inputSampleSize);
    }

    auto getOutputSample(std::size_t sampleIndex) const
    {
        return ArrayView<Type const>(m_outputData.data() + m_outputSampleSize * sampleIndex, m_outputSampleSize);
    }

private:
    std::size_t m_inputSampleSize;
    std::vector<Type> m_inputData;

    std::size_t m_outputSampleSize = 10;
    std::vector<Type> m_outputData;
};

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

//    void learnNetwork(ArrayView<BNN_TYPE> inputData)


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
