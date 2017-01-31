#include "Math.hpp"
#include <cassert>
#include <xmmintrin.h>

namespace
{

ArrayView<float const> getNthLayerWeights(ArrayView<float const> weightsMatrix,
                                          std::size_t numInputs,
                                          std::size_t layerIndex)
{
    auto layerSize = (numInputs + 1u);
    auto layerStart = layerSize * layerIndex;
    return weightsMatrix(layerStart, layerStart + layerSize);
}

float calculateSingleOutput(ArrayView<float const> input,
                            ArrayView<float const> weights)
{
    float output = weights[0];
    for(auto i = 0u; i < input.size(); ++i)
    {
        output += input[i] * weights[i + 1];
    }
    return output;
}

}

void vectorMatrixMultiplyFloat(ArrayView<float const> inputVector,
                               ArrayView<float const> weightsMatrix,
                               ArrayView<float> outputVector)
{
    for(auto i = 0u; i < outputVector.size(); ++i)
    {
        outputVector[i]  = calculateSingleOutput(inputVector,
                                                 getNthLayerWeights(weightsMatrix,
                                                                    inputVector.size(),
                                                                    i));
    }
}


void vectorMatrixMultiplyUnalignedFloat4(ArrayView<float const> inputVector,
                                         ArrayView<float const> weightsMatrix,
                                         ArrayView<float> outputVector)
{
    assert((inputVector.size() % 4) == 0);
    assert((outputVector.size() % 4) == 0);
    assert((outputVector.size() + 1) * inputVector.size() == weightsMatrix.size());

    auto rowSize = inputVector.size() + 1;
    for(auto i = 0u; i < outputVector.size(); i++)
    {
        outputVector[i] = weightsMatrix[i * rowSize];   // TODO maybe do it at the end?
    }

    for(auto i = 0u; i < inputVector.size(); i += 4)
    {
        auto x1 = _mm_set1_ps(inputVector[i]);
        auto x2 = _mm_set1_ps(inputVector[i + 1]);
        auto x3 = _mm_set1_ps(inputVector[i + 2]);
        auto x4 = _mm_set1_ps(inputVector[i + 3]);

        for(auto k = 0u; k < outputVector.size(); k += 4)
        {
            auto z = _mm_loadu_ps(&outputVector[k]);    // TODO think of making it aligned
            auto w1 = _mm_loadu_ps(&weightsMatrix[k * rowSize + i + 1]);
            auto w2 = _mm_loadu_ps(&weightsMatrix[(k + 1) * rowSize + i + 1]);
            auto w3 = _mm_loadu_ps(&weightsMatrix[(k + 2) * rowSize + i + 1]);
            auto w4 = _mm_loadu_ps(&weightsMatrix[(k + 3) * rowSize + i + 1]);

            _MM_TRANSPOSE4_PS(w1, w2, w3, w4);  // TODO maybe can arrange those data to be already transposed?

            auto xw1 = _mm_mul_ps(x1, w1);
            auto xw2 = _mm_mul_ps(x2, w2);
            auto xw3 = _mm_mul_ps(x3, w3);
            auto xw4 = _mm_mul_ps(x4, w4);

            auto xw12 = _mm_add_ps(xw1, xw2);
            auto xw34 = _mm_add_ps(xw3, xw4);
            auto xw1234 = _mm_add_ps(xw12, xw34);

            auto r = _mm_add_ps(z, xw1234);

            _mm_storeu_ps(&outputVector[k], r);
        }
    }
}
