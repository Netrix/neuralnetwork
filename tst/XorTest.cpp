#include <gtest/gtest.h>
#include "Nodes/MultipleInputLayerNodes/PassThroughMultipleInputLayerNode.hpp"
#include "LayeredNetworkBuilder.hpp"
#include "LayeredNetworkBuilders/FullyConnectedLayerSpecs.hpp"
#include "LayeredNetworkBuilders/FullyConnectedLayerBuilder.hpp"
#include "LayeredNetworkBuilders/InputLayerSpecs.hpp"
#include "StreamOperators.hpp"
#include "Utils/MathVectorAdapter.hpp"
#include "NormalDistributionGenerator.hpp"
#include "PassThroughLayerNodeFactories/TanhLayer.hpp"
#include <random>
#include <iomanip>


template<class Type>
struct TrainingEntity
{
    std::vector<Type> input;
    std::vector<Type> output;
};

TEST(XorTest, XorWithZeros)
{
    std::vector<TrainingEntity<float>> TRAIN_DATA = {
        {{ 1.0, 1.0 }, {0.0, 1.0}},
        {{ 1.0, 0.0 }, {1.0, 0.0}},
        {{ 0.0, 1.0 }, {1.0, 0.0}},
        {{ 0.0, 0.0 }, {0.0, 1.0}},
    };

    LayeredNetworkBuilder LayeredNetworkBuilder;
    auto outLayer = LayeredNetworkBuilder.setOutputLayer(FullyConnectedLayerSpecs{std::make_unique<TanhLayerNodeFactory<BNN_TYPE>>(1.0f), 2});
    auto hiddenLayer = outLayer->setInputLayer(FullyConnectedLayerSpecs{std::make_unique<TanhLayerNodeFactory<BNN_TYPE>>(1.0f), 2});
    hiddenLayer->setInputLayer(InputLayerSpecs{2});
    auto network = LayeredNetworkBuilder.buildBackPropagationNetwork();
    network->setLearningRate(0.01f);
    network->setVariables(NormalDistributionGenerator<BNN_TYPE>(17, 0, 1e-1));


    for(int i = 0; i < 100; ++i)
    {
        BNN_TYPE errorSum = 0;
        for(auto const& trainEntity : TRAIN_DATA)
        {
            auto result = make_math_adapter(network->forwardPass(trainEntity.input));
            std::cout << std::fixed << std::setprecision(2) << "Input: " << trainEntity.input << ", expected result: " <<trainEntity.output << ", result: " << result << std::endl;
            auto expected = make_math_adapter(trainEntity.output);
            auto error = expected - result;
            network->backPropagate(error);

            auto squaredError = error * error;
            errorSum += squaredError.sum();
        }
        network->applyDeltaOnVariables();
        std::cout << "errorSum: " << errorSum <<  std::endl;
    }
}

TEST(XorTest, XorWithMinusOnes)
{
    std::vector<TrainingEntity<float>> TRAIN_DATA = {
        {{ 1.0, 1.0 }, {1.0, 0.0}},
        {{ 1.0, -1.0 }, {0.0, 1.0}},
        {{ -1.0, 1.0 }, {0.0, 1.0}},
        {{ -1.0, -1.0 }, {1.0, 0.0}},
    };

    LayeredNetworkBuilder LayeredNetworkBuilder;
    auto outLayer = LayeredNetworkBuilder.setOutputLayer(FullyConnectedLayerSpecs{std::make_unique<TanhLayerNodeFactory<BNN_TYPE>>(1.0f), 2});
    auto hiddenLayer = outLayer->setInputLayer(FullyConnectedLayerSpecs{std::make_unique<TanhLayerNodeFactory<BNN_TYPE>>(1.0f), 2});
    hiddenLayer->setInputLayer(InputLayerSpecs{2});
    auto network = LayeredNetworkBuilder.buildBackPropagationNetwork();
    network->setLearningRate(0.01f);

    std::mt19937 mt(17);
    std::normal_distribution<> normal_dist(0, 1e-1);
    network->setVariables([&normal_dist, &mt]
    {
        return normal_dist(mt);
    });


    for(int i = 0; i < 100; ++i)
    {
        BNN_TYPE errorSum = 0;
        for(auto const& trainEntity : TRAIN_DATA)
        {
            auto result = make_math_adapter(network->forwardPass(trainEntity.input));
            std::cout << std::fixed << std::setprecision(2) << "Input: " << trainEntity.input << ", expected result: " <<trainEntity.output << ", result: " << result << std::endl;
            auto expected = make_math_adapter(trainEntity.output);
            auto error = expected - result;
            network->backPropagate(error);

            auto squaredError = error * error;
            errorSum += squaredError.sum();
        }
        network->applyDeltaOnVariables();
        std::cout << "errorSum: " << errorSum <<  std::endl;
    }
}
