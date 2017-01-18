#include <iostream>
#include <vector>
#include <memory>
#include <cassert>

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

//

template<class Type>
struct NotNull
{
    NotNull(Type* pointer)
        : m_pointer(pointer)
    {
        assert(pointer != nullptr);
    }

    NotNull(std::nullptr_t) = delete;

    Type* operator->()
    {
        return m_pointer;
    }

    Type const* operator->() const
    {
        return m_pointer;
    }

    Type& operator*()
    {
        return *m_pointer;
    }

    Type const& operator*() const
    {
        return *m_pointer;
    }

    Type** operator&()
    {
        return *m_pointer;
    }

    Type* const* operator&() const
    {
        return *m_pointer;
    }

private:
    Type* m_pointer;
};

struct BinaryNode{};
struct Variable{};
struct Const{};

struct ConstNodeBuilder;
struct VariableNodeBuilder;
struct BinaryNodeBuilder;

struct BuilderStorage
{
    std::vector<std::unique_ptr<ConstNodeBuilder>> consts;
    std::vector<std::unique_ptr<VariableNodeBuilder>> variables;
    std::vector<std::unique_ptr<BinaryNodeBuilder>> operations; // should have generic operations later
};

struct NodeBuilder
{
};

struct ConstNodeBuilder : NodeBuilder
{
};

struct VariableNodeBuilder : NodeBuilder
{
};

struct BinaryNodeBuilder : NodeBuilder
{
    BinaryNodeBuilder(BuilderStorage& builderStorage, std::string const& operation)
        : m_builderStorage(builderStorage)
        , m_operation(operation)
    {
    }

    NotNull<BinaryNodeBuilder> setFirstInput(BinaryNode, std::string const& operation)
    {
        assert(m_inputBuilders[0] == nullptr);
        auto l_builder = std::make_unique<BinaryNodeBuilder>(m_builderStorage, operation);
        m_inputBuilders[0] = l_builder.get();
        m_builderStorage.operations.push_back(std::move(l_builder));
        return m_builderStorage.operations.back().get();
    }

    NotNull<BinaryNodeBuilder> setSecondInput(BinaryNode, std::string const& operation)
    {
        assert(m_inputBuilders[1] == nullptr);
        auto l_builder = std::make_unique<BinaryNodeBuilder>(m_builderStorage, operation);
        m_inputBuilders[1] = l_builder.get();
        m_builderStorage.operations.push_back(std::move(l_builder));
        return m_builderStorage.operations.back().get();
    }

    NotNull<VariableNodeBuilder> setFirstInput(Variable);
    NotNull<VariableNodeBuilder> setSecondInput(Variable);
    NotNull<ConstNodeBuilder> setFirstInput(Const);
    NotNull<ConstNodeBuilder> setSecondInput(Const);
    void setFirstInput(NotNull<ConstNodeBuilder>);
    void setSecondInput(NotNull<ConstNodeBuilder>);

private:
    void setFirstInput(NodeBuilder*)

private:
    BuilderStorage& m_builderStorage;
    std::string m_operation;

    std::array<NodeBuilder*, 2> m_inputBuilders{};
};


struct BackPropagationNetwork{};
struct ForwardNetwork{};

struct NetworkBuilder
{
    NotNull<BinaryNodeBuilder> setRootNode(BinaryNode, std::string const& operation)
    {
        auto l_builder = std::make_unique<BinaryNodeBuilder>(m_storage, operation);
        m_storage.operations.push_back(std::move(l_builder));
        return m_storage.operations.back().get();
    }

    std::unique_ptr<BackPropagationNetwork> buildBackPropagationNetwork();   // should verify entire tree and return ready to work tree

    std::unique_ptr<ForwardNetwork> buildForwardNetwork();

private:
    BuilderStorage m_storage;
    BinaryNodeBuilder* m_root; // should be generic operation later // should be able to get topology from here to get forward list to do operations
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
    auto yNode = builder.setRootNode(BinaryNode{}, "add");
    auto ySubNode = yNode->setFirstInput(BinaryNode{}, "add");  // n1 + n2 + 2 -> n3 -> y

    auto n1wMulNode = ySubNode->setFirstInput(BinaryNode{}, "mul");
    auto n2wMulNode = ySubNode->setSecondInput(BinaryNode{}, "mul");
    yNode->setSecondInput(Variable{}); // w30

    n1wMulNode->setFirstInput(Variable{}); // w31
    n2wMulNode->setFirstInput(Variable{}); // w32

    auto n1Node = n1wMulNode->setSecondInput(BinaryNode{}, "sum");
    auto n2Node = n2wMulNode->setSecondInput(BinaryNode{}, "sum");

    auto n1SubNode = n1Node->setFirstInput(BinaryNode{}, "sum");
    auto n2SubNode = n2Node->setFirstInput(BinaryNode{}, "sum");

    n1Node->setSecondInput(Variable{}); // w10
    n2Node->setSecondInput(Variable{}); // w20

    auto x1w11MulNode = n1SubNode->setFirstInput(BinaryNode{}, "mul");
    auto x2w12MulNode = n1SubNode->setSecondInput(BinaryNode{}, "mul");

    auto x1w21MulNode = n2SubNode->setFirstInput(BinaryNode{}, "mul");
    auto x2w22MulNode = n2SubNode->setSecondInput(BinaryNode{}, "mul");

    auto x1Node = x1w11MulNode->setFirstInput(Const{});
    x1w11MulNode->setSecondInput(Variable{}); // w11

    auto x2Node = x2w12MulNode->setFirstInput(Const{});
    x2w12MulNode->setSecondInput(Variable{}); // w12

    x1w21MulNode->setFirstInput(x1Node);
    x1w21MulNode->setSecondInput(Variable{}); // w21

    x2w22MulNode->setFirstInput(x2Node);
    x2w22MulNode->setSecondInput(Variable{}); // w22

    auto network = builder.buildBackPropagationNetwork();

    // epoch learn above data
    std::cout << "Hello" << std::endl;
}
