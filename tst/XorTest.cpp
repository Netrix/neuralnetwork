#include <gtest/gtest.h>
#include "Nodes/LayerNodes/PassThroughLayerNode.hpp"
#include "LayeredNetworkBuilder.hpp"
#include "LayeredNetworkBuilders/FullyConnectedLayerSpecs.hpp"
#include "LayeredNetworkBuilders/FullyConnectedLayerBuilder.hpp"
#include "LayeredNetworkBuilders/InputLayerSpecs.hpp"
#include "StreamOperators.hpp"
#include "MathVectorAdapter.hpp"
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
    auto outLayer = LayeredNetworkBuilder.setOutputLayer(FullyConnectedLayerSpecs{2, "tanh"});
    auto hiddenLayer = outLayer->setInputLayer(FullyConnectedLayerSpecs{2, "tanh"});
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

TEST(XorTest, XorWithMinusOnes)
{
    std::vector<TrainingEntity<float>> TRAIN_DATA = {
        {{ 1.0, 1.0 }, {1.0, 0.0}},
        {{ 1.0, -1.0 }, {0.0, 1.0}},
        {{ -1.0, 1.0 }, {0.0, 1.0}},
        {{ -1.0, -1.0 }, {1.0, 0.0}},
    };

    LayeredNetworkBuilder LayeredNetworkBuilder;
    auto outLayer = LayeredNetworkBuilder.setOutputLayer(FullyConnectedLayerSpecs{2, "tanh"});
    auto hiddenLayer = outLayer->setInputLayer(FullyConnectedLayerSpecs{2, "tanh"});
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
