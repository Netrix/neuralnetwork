#include <gtest/gtest.h>
#include "Nodes/MultipleInputLayerNodes/PassThroughMultipleInputLayerNode.hpp"

struct PassThroughMultipleInputLayerNodeTest : testing::Test
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

    float output;
};


TEST_F(PassThroughMultipleInputLayerNodeTest, PassThroughTest)
{
    CustomComputationNode first{5}, second{7};
    std::vector<NotNull<ComputationNode<float>>> inputs = { &first, &second };


    PassThroughMultipleInputLayerNode<float> sut{inputs};

    sut.forwardPass();
    EXPECT_EQ(sut.getOutputValues()[0], first.output);
    EXPECT_EQ(sut.getOutputValues()[1], second.output);

    std::vector<float> errors = { 1, 2 };
    sut.backPropagate(errors);
}
