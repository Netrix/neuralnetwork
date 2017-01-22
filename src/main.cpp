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
    std::vector<TrainingEntity<float>> TRAIN_DATA = {
        {{ 1.0, 1.0 }, {0.0}},
        {{ 1.0, 0.0 }, {1.0}},
        {{ 0.0, 1.0 }, {1.0}},
        {{ 0.0, 0.0 }, {0.0}},
    };

//    std::vector<TrainingEntity<float>> TRAIN_DATA = {
//        {{ 1.0, 1.0 }, {-1.0}},
//        {{ 1.0, -1.0 }, {1.0}},
//        {{ -1.0, 1.0 }, {1.0}},
//        {{ 1.0, -1.0 }, {-1.0}},
//    };

    NetworkBuilder builder;
    auto sigmoidNode = builder.setRootNode(UnaryNodeTag{}, "tanh");
    auto yNode = sigmoidNode->setInput(MultipleInputTag{}, "add");

    auto n1wMulNode = yNode->addInput(BinaryNodeTag{}, "mul");
    auto n2wMulNode = yNode->addInput(BinaryNodeTag{}, "mul");
    yNode->addInput(VariableTag{}); // w30

    n1wMulNode->setFirstInput(VariableTag{}); // w31
    n2wMulNode->setFirstInput(VariableTag{}); // w32

    auto n1NodeSigmoid = n1wMulNode->setSecondInput(UnaryNodeTag{}, "tanh");
    auto n2NodeSigmoid = n2wMulNode->setSecondInput(UnaryNodeTag{}, "tanh");

    auto n1Node = n1NodeSigmoid->setInput(MultipleInputTag{}, "add");
    auto n2Node = n2NodeSigmoid->setInput(MultipleInputTag{}, "add");

    n1Node->addInput(VariableTag{}); // w10
    n2Node->addInput(VariableTag{}); // w20

    auto x1w11MulNode = n1Node->addInput(BinaryNodeTag{}, "mul");   // TODO can put "mul" into tag!
    auto x2w12MulNode = n1Node->addInput(BinaryNodeTag{}, "mul");

    auto x1w21MulNode = n2Node->addInput(BinaryNodeTag{}, "mul");
    auto x2w22MulNode = n2Node->addInput(BinaryNodeTag{}, "mul");

    auto x1Node = x1w11MulNode->setFirstInput(ConstTag{});
    x1w11MulNode->setSecondInput(VariableTag{}); // w11

    auto x2Node = x2w12MulNode->setFirstInput(ConstTag{});
    x2w12MulNode->setSecondInput(VariableTag{}); // w12

    x1w21MulNode->setFirstInput(x1Node);
    x1w21MulNode->setSecondInput(VariableTag{}); // w21

    x2w22MulNode->setFirstInput(x2Node);
    x2w22MulNode->setSecondInput(VariableTag{}); // w22

//    auto network = builder.buildBackPropagationNetwork();

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
    // 1, Create higher abstraction builder that can automatically build layers from smaller nodes
    // 2. abstract initialization of weights
    // 3. multiple output layer (sigmoid, tanh, relu)


    // epoch learn above data
    std::cout << "Hello" << std::endl;
}
