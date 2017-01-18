#include <iostream>
#include <vector>

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

struct IConstNodeBuilder
{
};

struct IVariableNodeBuilder
{
};

struct IBinaryNodeBuilder
{
    IBinaryNodeBuilder* setFirstInput(BinaryNode, std::string const& operation);
    IBinaryNodeBuilder* setSecondInput(BinaryNode, std::string const& operation);
    IVariableNodeBuilder* setFirstInput(Variable);
    IVariableNodeBuilder* setSecondInput(Variable);
    IConstNodeBuilder* setFirstInput(Const);
    IConstNodeBuilder* setSecondInput(Const);
};

struct BinaryNode{};

struct BackPropagationNetwork{};
struct ForwardNetwork{};

struct NetworkBuilder
{
    struct BuilderStorage
    {
        std::vector<std::unique_ptr<IConstNodeBuilder>> consts;
        std::vector<std::unique_ptr<IVariableNodeBuilder>> variables;
        std::vector<std::unique_ptr<IBinaryNodeBuilder>> operations; // should have generic operations later
    };

    IBinaryNodeBuilder* setRootNode(BinaryNode, std::string const& operation);

    std::unique_ptr<BackPropagationNetwork> buildBackPropagationNetwork();   // should verify entire tree and return ready to work tree

    std::unique_ptr<ForwardNetwork> buildForwardNetwork();

private:
    BuilderStorage m_storage;
    IBinaryNodeBuilder* m_root; // should be generic operation later // should be able to get topology from here to get forward list to do operations
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
    auto yNode = builder.setRootNode(Binary, "add");
    auto ySubNode = addNode->setFirstInput(BinaryNode, "add");  // n1 + n2 + 2 -> n3 -> y
    
    auto n1wMulNode = ySubNode->setFirstInput(BinaryNode, "mul");
    auto n2wMulNode = ySubNode->setSecondInput(BinaryNode, "mul");
    yNode->setSecondInput(Variable); // w30

    n1wMulNode->setFirstInput(Variable); // w31
    n2wMulNode->setFirstInput(Variable); // w32

    auto n1Node = n1wMulNode->setSecondInput(BinaryNode, "sum");
    auto n2Node = n2wMulNode->setSecondInput(BinaryNode, "sum");

    auto n1SubNode = n1Node->setFirstInput(BinaryNode, "sum");
    auto n2SubNode = n2Node->setFirstInput(BinaryNode, "sum");

    n1Node->setSecondInput(Variable); // w10
    n2Node->setSecondInput(Variable); // w20

    auto x1w11MulNode = n1SubNode->setFirstInput(BinaryNode, "mul");
    auto x2w12MulNode = n1SubNode->setSecondInput(BinaryNode, "mul");

    auto x1w21MulNode = n2SubNode->setFirstInput(BinaryNode, "mul");
    auto x2w22MulNode = n2SubNode->setSecondInput(BinaryNode, "mul");

    auto x1Node = x1w11MulNode->setFirstInput(Const);
    x1w11MulNode->setSecondInput(Variable); // w11

    auto x2Node = x2w12MulNode->setFirstInput(Const);
    x2w12MulNode->setSecondInput(Variable); // w12

    x1w21MulNode->setFirstInput(x1Node);
    x1w21MulNode->setSecondInput(Variable); // w21

    x2w22MulNode->setFirstInput(x2Node);
    x2w22MulNode->setSecondInput(Variable); // w22

    auto network = builder.build();

    // epoch learn above data
    std::cout << "Hello" << std::endl;
}
