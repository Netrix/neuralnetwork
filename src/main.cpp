#include <iostream>
#include <vector>
#include <memory>
#include <cassert>
#include <random>
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


template<class Type>
struct TrainingEntity
{
    std::vector<Type> input;
    std::vector<Type> output;
};

std::ostream& operator<<(std::ostream& out, std::vector<BNN_TYPE> const& values)
{
    out << " [ ";
    for(auto a : values)
    {
        out << a << ", ";
    }
    return out << " ] ";
}


int main()
{
//    std::vector<TrainingEntity<float>> TRAIN_DATA = {
//        {{ 1.0, 1.0 }, {0.0}},
//        {{ 1.0, 0.0 }, {1.0}},
//        {{ 0.0, 1.0 }, {1.0}},
//        {{ 0.0, 0.0 }, {0.0}},
//    };

    std::vector<TrainingEntity<float>> TRAIN_DATA = {
        {{ 1.0, 1.0 }, {-1.0}},
        {{ 1.0, -1.0 }, {1.0}},
        {{ -1.0, 1.0 }, {1.0}},
        {{ 1.0, -1.0 }, {-1.0}},
    };

    LayeredNetworkBuilder LayeredNetworkBuilder;
    auto outLayer = LayeredNetworkBuilder.setOutputLayer(FullyConnectedLayerSpecs{1, "tanh"});
    auto hiddenLayer = outLayer->setInputLayer(FullyConnectedLayerSpecs{2, "tanh"});
    hiddenLayer->setInputLayer(InputLayerSpecs{2});
    auto network = LayeredNetworkBuilder.buildBackPropagationNetwork();

    std::mt19937 mt(2);
    std::normal_distribution<> normal_dist(0, 1);
    network->setVariables([&normal_dist, &mt]
    {
        return normal_dist(mt);
    });

    auto l_print_network = [&]{
        for(int i = 0; i < TRAIN_DATA.size(); ++i)
        {
            std::cout << "Input: " << TRAIN_DATA[i].input << ", expected result: " << TRAIN_DATA[i].output[0] << ", result: " << network->forwardPass(TRAIN_DATA[i].input)[0] << std::endl;
        }
    };

    for(int i = 0; i < 5000; ++i)
    {
        BNN_TYPE errorSum = 0;
        for(auto const& trainEntity : TRAIN_DATA)
        {
            auto result = network->forwardPass(trainEntity.input)[0];
            auto error = trainEntity.output[0] - result;
            network->backPropagate(error);

            auto squaredError = error * error;
            errorSum += squaredError;
        }
        network->applyDeltaOnVariables();
        std::cout << "errorSum: " << errorSum <<  std::endl;
        l_print_network();
    }

    // TODO
    // 0. Make relu work!
    // 2. abstract initialization of weights
    // 3. multiple output layer (sigmoid, tanh, relu)
    // 4. abstract backprop


    // epoch learn above data
    std::cout << "Hello" << std::endl;
}
