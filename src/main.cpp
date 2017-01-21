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

template<class Type>
struct Multiplication
{
//    Type calculate(
};

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
//        {{ 1.0, 1.0 }, {1.0}},
//        {{ 1.0, -1.0 }, {-1.0}},
//        {{ -1.0, 1.0 }, {-1.0}},
        {{ 1.0, 0.0 }, {0.0}},
    };

    NetworkBuilder builder;
    auto sigmoidNode = builder.setRootNode(UnaryNodeTag{}, "sigmoid");
    auto yNode = sigmoidNode->setInput(BinaryNodeTag{}, "add");
//    auto yNode = builder.setRootNode(BinaryNodeTag{}, "add");
    auto ySubNode = yNode->setFirstInput(BinaryNodeTag{}, "add");  // n1 + n2 + 2 -> n3 -> y

    auto n1wMulNode = ySubNode->setFirstInput(BinaryNodeTag{}, "mul");
    auto n2wMulNode = ySubNode->setSecondInput(BinaryNodeTag{}, "mul");
    yNode->setSecondInput(VariableTag{}); // w30

    n1wMulNode->setFirstInput(VariableTag{}); // w31
    n2wMulNode->setFirstInput(VariableTag{}); // w32

    auto n1NodeSigmoid = n1wMulNode->setSecondInput(UnaryNodeTag{}, "sigmoid");
    auto n2NodeSigmoid = n2wMulNode->setSecondInput(UnaryNodeTag{}, "sigmoid");

    auto n1Node = n1NodeSigmoid->setInput(BinaryNodeTag{}, "add");
    auto n2Node = n2NodeSigmoid->setInput(BinaryNodeTag{}, "add");

//    auto n1Node = n1wMulNode->setSecondInput(BinaryNodeTag{}, "add");
//    auto n2Node = n2wMulNode->setSecondInput(BinaryNodeTag{}, "add");

    auto n1SubNode = n1Node->setFirstInput(BinaryNodeTag{}, "add");
    auto n2SubNode = n2Node->setFirstInput(BinaryNodeTag{}, "add");

    n1Node->setSecondInput(VariableTag{}); // w10
    n2Node->setSecondInput(VariableTag{}); // w20

    auto x1w11MulNode = n1SubNode->setFirstInput(BinaryNodeTag{}, "mul");
    auto x2w12MulNode = n1SubNode->setSecondInput(BinaryNodeTag{}, "mul");

    auto x1w21MulNode = n2SubNode->setFirstInput(BinaryNodeTag{}, "mul");
    auto x2w22MulNode = n2SubNode->setSecondInput(BinaryNodeTag{}, "mul");

    auto x1Node = x1w11MulNode->setFirstInput(ConstTag{});
    x1w11MulNode->setSecondInput(VariableTag{}); // w11

    auto x2Node = x2w12MulNode->setFirstInput(ConstTag{});
    x2w12MulNode->setSecondInput(VariableTag{}); // w12

    x1w21MulNode->setFirstInput(x1Node);
    x1w21MulNode->setSecondInput(VariableTag{}); // w21

    x2w22MulNode->setFirstInput(x2Node);
    x2w22MulNode->setSecondInput(VariableTag{}); // w22

    auto network = builder.buildBackPropagationNetwork();

    std::mt19937 mt(2);
    std::normal_distribution<> normal_dist(0, 2);

    std::vector<float> weights(9);
    for(auto & w : weights)
    {
        w = normal_dist(mt);
        std::cout << w << ", ";
    }
    std::cout << std::endl;

    network->setVariables(weights);
//    auto result = network->forwardPass(TRAIN_DATA[1].input)[0];
//    auto error = TRAIN_DATA[1].output[0] - result;
//    std::cout << result << ", error: " << error <<  std::endl;
//    network->backPropagate(error);

    auto l_print_network = [&]{
        for(int i = 0; i < TRAIN_DATA.size(); ++i)
        {
            std::cout << "Input: " << TRAIN_DATA[i].input << ", expected result: " << TRAIN_DATA[i].output[0] << ", result: " << network->forwardPass(TRAIN_DATA[i].input)[0] << std::endl;
        }
    };

    for(int i = 0; i < 10; ++i)
    {
        BNN_TYPE errorSum = 0;
        for(auto const& trainEntity : TRAIN_DATA)
        {
            auto result = network->forwardPass(trainEntity.input)[0];
            auto error = trainEntity.output[0] - result;
            std::cout << "backprop error: " << error <<  std::endl;
            network->backPropagate(error);

            auto squaredError = error * error;
            std::cout << squaredError << std::endl;
            errorSum += squaredError;
        }
        network->applyDeltaOnVariables();
        std::cout << "errorSum: " << errorSum <<  std::endl;
        l_print_network();
//        result = network->forwardPass(TRAIN_DATA[1].input)[0];
//        error = TRAIN_DATA[1].output[0] - result;
//        std::cout << result << ", error: " << error <<  std::endl;
//        network->backPropagate(error);
    }

//    NetworkBuilder builder2;
//    auto l_mul = builder2.setRootNode(BinaryNodeTag{}, "add");
//    auto l_x1 = l_mul->setFirstInput(ConstTag{});
//    auto l_x2 = l_mul->setSecondInput(ConstTag{});

//    auto mulNetwork = builder2.buildBackPropagationNetwork();
//    std::vector<float> l_input = { 3, 4 };
//    std::cout << mulNetwork->forwardPass(l_input)[0] << std::endl;

    // epoch learn above data
    std::cout << "Hello" << std::endl;
}
