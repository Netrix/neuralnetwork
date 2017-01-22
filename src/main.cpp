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

struct FullyConnectedTag{};
struct InputTag{};

struct LayerBuilder
{
    virtual ~LayerBuilder() = default;

    virtual std::size_t getNumOutputs() const = 0;
};

struct FullyConnectedLayerBuilder : LayerBuilder
{
    FullyConnectedLayerBuilder(std::size_t numNeurons, std::string const& activation)
        : m_numNeurons(numNeurons)
        , m_activation(activation)
    {
    }

    std::size_t getNumOutputs() const override
    {
        return m_numNeurons;
    }

private:
    std::size_t m_numNeurons;
    std::string  m_activation;
};

struct InputLayerBuilder : LayerBuilder
{
    InputLayerBuilder(std::size_t numInputs)
        : m_numInputs(numInputs)
    {}

    std::size_t getNumOutputs() const override
    {
        return m_numInputs;
    }

private:
    std::size_t m_numInputs;
};

struct LayerNetworkBuilder
{
    void addLayer(InputTag, std::size_t numInputs)
    {
        m_layerBuilders.push_back(std::make_unique<InputLayerBuilder>(numInputs));
    }

    void addLayer(FullyConnectedTag, std::size_t numNeurons, std::string const& activation)
    {
        m_layerBuilders.push_back(std::make_unique<FullyConnectedLayerBuilder>(numNeurons, activation));
    }

    std::unique_ptr<BackPropagationNetwork> buildBackPropagationNetwork()
    {
        assert(!m_layerBuilders.empty());
        assert(m_layerBuilders.back()->getNumOutputs() == 1);

        std::vector<LayerBuilder const*> reversedBuilders;
        reversedBuilders.reserve(m_layerBuilders.size());
        std::transform(std::rbegin(m_layerBuilders), std::rend(m_layerBuilders), std::back_inserter(reversedBuilders),
                       [](auto const& builder)
        {
            return builder.get();
        });

        NetworkBuilder networkBuilder;

        for(auto i = 0; i < reversedBuilders.size() - 1; ++i)
        {
        // 1. build output elements from previous layer
        // 2. build rest of the elements in current network
        // 3. go to 1.
        }

        return networkBuilder.buildBackPropagationNetwork();
    }

private:
    std::vector<std::unique_ptr<LayerBuilder>> m_layerBuilders;
};

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

    auto network = builder.buildBackPropagationNetwork();

    LayerNetworkBuilder layerNetworkBuilder;
    layerNetworkBuilder.addLayer(InputTag{}, 2);
    layerNetworkBuilder.addLayer(FullyConnectedTag{}, 2, "relu");
    layerNetworkBuilder.addLayer(FullyConnectedTag{}, 1, "relu");
    auto layerNetwork = layerNetworkBuilder.buildBackPropagationNetwork();

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
