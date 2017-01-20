#include <iostream>
#include <vector>
#include <memory>
#include <cassert>
#include "NotNull.hpp"
#include "NodeTags.hpp"
#include "NodeBuilder.hpp"
#include "BinaryNodeBuilder.hpp"
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

int main()
{
    std::vector<TrainingEntity<double>> TRAIN_DATA = {
        {{ 1.0, 1.0 }, {0.0}},
        {{ 1.0, 0.0 }, {1.0}},
        {{ 0.0, 1.0 }, {1.0}},
        {{ 0.0, 0.0 }, {0.0}},
    };

    NetworkBuilder builder;
    auto yNode = builder.setRootNode(BinaryNodeTag{}, "add");
    auto ySubNode = yNode->setFirstInput(BinaryNodeTag{}, "add");  // n1 + n2 + 2 -> n3 -> y

    auto n1wMulNode = ySubNode->setFirstInput(BinaryNodeTag{}, "mul");
    auto n2wMulNode = ySubNode->setSecondInput(BinaryNodeTag{}, "mul");
    yNode->setSecondInput(VariableTag{}); // w30

    n1wMulNode->setFirstInput(VariableTag{}); // w31
    n2wMulNode->setFirstInput(VariableTag{}); // w32

    auto n1Node = n1wMulNode->setSecondInput(BinaryNodeTag{}, "sum");
    auto n2Node = n2wMulNode->setSecondInput(BinaryNodeTag{}, "sum");

    auto n1SubNode = n1Node->setFirstInput(BinaryNodeTag{}, "sum");
    auto n2SubNode = n2Node->setFirstInput(BinaryNodeTag{}, "sum");

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

//    auto network = builder.buildBackPropagationNetwork();
//    network->forwardPass()


    NetworkBuilder builder2;
    auto l_mul = builder2.setRootNode(BinaryNodeTag{}, "mul");
    auto l_x1 = l_mul->setFirstInput(ConstTag{});
    auto l_x2 = l_mul->setSecondInput(ConstTag{});

    auto mulNetwork = builder2.buildBackPropagationNetwork();
    std::vector<float> l_input = { 3, 4 };
    std::cout << mulNetwork->forwardPass(l_input)[0] << std::endl;

    // epoch learn above data
    std::cout << "Hello" << std::endl;
}
