#include <gtest/gtest.h>
#include "Utils/Math.hpp"


TEST(MathTests, MathMultiply)
{
    std::vector<float> input(12, 1.0f);
    std::vector<float> outputs(8);
    std::vector<float> weights((12 + 1) * 8, 2.0f);

    vectorMatrixMultiplyFloat(input, weights, outputs);

    std::vector<float> outputsSse(8);

    vectorMatrixMultiplyUnalignedFloat4(input, weights, outputsSse);

    EXPECT_EQ(outputs, outputsSse);
}
