#include <gtest/gtest.h>
#include "Nodes/UnaryOperations/SigmoidUnaryOperation.hpp"

struct SigmoidUnaryOperationTest : testing::Test
{
};

struct CustomComputationNode : ComputationNode<float>
{
    CustomComputationNode(float v)
        : output(v)
    {}

    ArrayView<float const> getOutputValues() const override
    {
        return output;
    }

    void backPropagate(ArrayView<float const> v) override
    {
        std::cout << "propagated error " << v[0] << std::endl;
    }

    std::size_t getNumOutputs() const override
    {
        return 1;
    }

    void backPropagationPass() override
    {
    }

    float output;
};


TEST_F(SigmoidUnaryOperationTest, TestSetsCanBeCompared)
{
    CustomComputationNode input(4.0f);
    SigmoidUnaryOperationNode<float> sut(&input, 1.0);
    sut.forwardPass();
    std::cout << sut.getOutputValues()[0] << std::endl;

    float error = -1.0f;
    sut.backPropagate(error);
}
