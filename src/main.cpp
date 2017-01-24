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
        : m_numSamples(mnistData.labels.size())
        , m_inputSampleSize(mnistData.imageWidth * mnistData.imageHeight)
        , m_inputData(mnistData.imageData.size())
        , m_outputData(m_outputSampleSize * mnistData.labels.size())
    {
        assert(mnistData.labels.size() == (mnistData.imageData.size() / m_inputSampleSize));

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

    auto getNumSamples() const
    {
        return m_numSamples;
    }

private:
    std::size_t m_numSamples;

    std::size_t m_inputSampleSize;
    std::vector<Type> m_inputData;

    std::size_t m_outputSampleSize = 10;
    std::vector<Type> m_outputData;
};

    template<class Dataset, class Network>
    auto learnEpoch(Network & network, Dataset const& dataset, std::size_t batchSize)
    {
        BNN_TYPE errorSum = 0;
        for(std::size_t i = 0; i < dataset.getNumSamples();)
        {
            for(std::size_t k = 0; k < batchSize && i < dataset.getNumSamples(); ++i, ++k)
            {
                auto result = make_math_adapter(network->forwardPass(dataset.getInputSample(i)));
//                std::cout << std::fixed << std::setprecision(2) << "Input: " << trainEntity.input << ", expected result: " <<trainEntity.output << ", result: " << result << std::endl;
                auto expected = make_math_adapter(dataset.getOutputSample(i));
                auto error = expected - result;
                network->backPropagate(error);

                auto squaredError = error * error;
                errorSum += squaredError.sum();
            }
            network->applyDeltaOnVariables();
            std::cout << "batch completed, samples passed: " << i << "/" << dataset.getNumSamples() << std::endl;
        }
        return errorSum;
    }


int main()
{
    std::string imagesPath = "../../data/train-images-idx3-ubyte";
    std::string labelsPath = "../../data/train-labels-idx1-ubyte";

    auto mnistDataset = MnistPreprocessedDataSet<float>(loadMnistDataset(imagesPath, labelsPath));
    std::cout << mnistDataset.getInputSampleSize() << " " << mnistDataset.getNumSamples() << " " << mnistDataset.getOutputSampleSize() << std::endl;

    LayeredNetworkBuilder LayeredNetworkBuilder;
    auto outLayer = LayeredNetworkBuilder.setOutputLayer(FullyConnectedLayerSpecs{mnistDataset.getOutputSampleSize(), "relu"});
    auto hiddenLayer = outLayer->setInputLayer(FullyConnectedLayerSpecs{32, "relu"});
    hiddenLayer->setInputLayer(InputLayerSpecs{mnistDataset.getInputSampleSize()});
    auto network = LayeredNetworkBuilder.buildBackPropagationNetwork();
    network->setLearningRate(0.01f);

    network->setVariables(NormalDistributionGenerator<BNN_TYPE>(17, 0, 1e-1));


    for(int i = 0; i < 500; ++i)
    {
        auto errorSum = learnEpoch(network, mnistDataset, 256);
        std::cout << "epoch: " << i << " errorSum: " << errorSum <<  std::endl;

    }

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
