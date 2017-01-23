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
#include <valarray>


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

std::ostream& operator<<(std::ostream& out, ArrayView<BNN_TYPE const> const& values)
{
    out << " [ ";
    for(auto a : values)
    {
        out << a << ", ";
    }
    return out << " ] ";
}

template<class Type>
struct MathVectorAdapter
{
    template<class Container>
    MathVectorAdapter(Container const& c)
        : m_values(std::begin(c), std::end(c))
    {}

    MathVectorAdapter<Type> operator-(MathVectorAdapter<Type> const& ref)
    {
        return getBinaryResult(ref, [](auto a, auto b)
        {
            return a - b;
        });
    }

    MathVectorAdapter<Type> operator*(MathVectorAdapter<Type> const& ref)
    {
        return getBinaryResult(ref, [](auto a, auto b)
        {
            return a * b;
        });
    }

    operator ArrayView<Type const>() const
    {
        return m_values;
    }

    operator ArrayView<Type>()
    {
        return m_values;
    }

    auto sum() const
    {
        return std::accumulate(std::begin(m_values), std::end(m_values), Type{});
    }

private:
    template<class Functor>
    auto getBinaryResult(MathVectorAdapter<Type> const& ref, Functor f)
    {
        std::vector<Type> results;
        results.reserve(m_values.size());

        std::transform(std::begin(m_values), std::end(m_values), std::begin(ref.m_values), std::back_inserter(results), f);
        return MathVectorAdapter<Type>(results);
    }

private:
    std::vector<Type> m_values;
};

template<class Type>
auto make_math_adapter(Type const& args)
{
    return MathVectorAdapter<typename std::remove_cv<typename Type::value_type>::type>(args);
}

int main()
{
//    std::vector<TrainingEntity<float>> TRAIN_DATA = {
//        {{ 1.0, 1.0 }, {0.0, 1.0}},
//        {{ 1.0, 0.0 }, {1.0, 0.0}},
//        {{ 0.0, 1.0 }, {1.0, 0.0}},
//        {{ 0.0, 0.0 }, {0.0, 1.0}},
//    };

    std::vector<TrainingEntity<float>> TRAIN_DATA = {
        {{ 1.0, 1.0 }, {1.0, 0.0}},
        {{ 1.0, -1.0 }, {0.0, 1.0}},
        {{ -1.0, 1.0 }, {0.0, 1.0}},
        {{ -1.0, -1.0 }, {1.0, 0.0}},
    };

    LayeredNetworkBuilder LayeredNetworkBuilder;
    auto outLayer = LayeredNetworkBuilder.setOutputLayer(FullyConnectedLayerSpecs{2, "relu"});
    auto hiddenLayer = outLayer->setInputLayer(FullyConnectedLayerSpecs{2, "relu"});
    hiddenLayer->setInputLayer(InputLayerSpecs{2});
    auto network = LayeredNetworkBuilder.buildBackPropagationNetwork();
    network->setLearningRate(0.1f);

    std::mt19937 mt(17);
    std::normal_distribution<> normal_dist(0, 1e-2);
    network->setVariables([&normal_dist, &mt]
    {
        return normal_dist(mt);
    });

    auto l_print_network = [&]{
        for(int i = 0; i < TRAIN_DATA.size(); ++i)
        {
            std::cout << std::fixed << std::setprecision(2) << "Input: " << TRAIN_DATA[i].input << ", expected result: " << TRAIN_DATA[i].output << ", result: " << network->forwardPass(TRAIN_DATA[i].input) << std::endl;
        }
    };

    for(int i = 0; i < 5000; ++i)
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
//        l_print_network();
    }

    // TODO
    // 0. Make relu work!
    // 2. abstract initialization of weightsl
    // 3. multiple output layer (sigmoid, tanh, relu)
    // 4. abstract backprop
    //
    // zero-centering data! mean centering


    // epoch learn above data
    std::cout << "Hello" << std::endl;
}
