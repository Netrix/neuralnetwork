#include "Math.hpp"
#include <cassert>
#include <immintrin.h>

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

inline void transpose8_ps(__m256 &row0,
                          __m256 &row1,
                          __m256 &row2,
                          __m256 &row3,
                          __m256 &row4,
                          __m256 &row5,
                          __m256 &row6,
                          __m256 &row7)
{
    __m256 __t0, __t1, __t2, __t3, __t4, __t5, __t6, __t7;
    __m256 __tt0, __tt1, __tt2, __tt3, __tt4, __tt5, __tt6, __tt7;
    __t0 = _mm256_unpacklo_ps(row0, row1);
    __t1 = _mm256_unpackhi_ps(row0, row1);
    __t2 = _mm256_unpacklo_ps(row2, row3);
    __t3 = _mm256_unpackhi_ps(row2, row3);
    __t4 = _mm256_unpacklo_ps(row4, row5);
    __t5 = _mm256_unpackhi_ps(row4, row5);
    __t6 = _mm256_unpacklo_ps(row6, row7);
    __t7 = _mm256_unpackhi_ps(row6, row7);
    __tt0 = _mm256_shuffle_ps(__t0,__t2,_MM_SHUFFLE(1,0,1,0));
    __tt1 = _mm256_shuffle_ps(__t0,__t2,_MM_SHUFFLE(3,2,3,2));
    __tt2 = _mm256_shuffle_ps(__t1,__t3,_MM_SHUFFLE(1,0,1,0));
    __tt3 = _mm256_shuffle_ps(__t1,__t3,_MM_SHUFFLE(3,2,3,2));
    __tt4 = _mm256_shuffle_ps(__t4,__t6,_MM_SHUFFLE(1,0,1,0));
    __tt5 = _mm256_shuffle_ps(__t4,__t6,_MM_SHUFFLE(3,2,3,2));
    __tt6 = _mm256_shuffle_ps(__t5,__t7,_MM_SHUFFLE(1,0,1,0));
    __tt7 = _mm256_shuffle_ps(__t5,__t7,_MM_SHUFFLE(3,2,3,2));
    row0 = _mm256_permute2f128_ps(__tt0, __tt4, 0x20);
    row1 = _mm256_permute2f128_ps(__tt1, __tt5, 0x20);
    row2 = _mm256_permute2f128_ps(__tt2, __tt6, 0x20);
    row3 = _mm256_permute2f128_ps(__tt3, __tt7, 0x20);
    row4 = _mm256_permute2f128_ps(__tt0, __tt4, 0x31);
    row5 = _mm256_permute2f128_ps(__tt1, __tt5, 0x31);
    row6 = _mm256_permute2f128_ps(__tt2, __tt6, 0x31);
    row7 = _mm256_permute2f128_ps(__tt3, __tt7, 0x31);
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
    assert((inputVector.size() + 1) * outputVector.size() == weightsMatrix.size());

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

void vectorMatrixMultiplyUnalignedFloat8(ArrayView<float const> inputVector,
                                         ArrayView<float const> weightsMatrix,
                                         ArrayView<float> outputVector)
{
    assert((inputVector.size() % 8) == 0);
    assert((outputVector.size() % 8) == 0);
    assert((inputVector.size() + 1) * outputVector.size() == weightsMatrix.size());

    auto rowSize = inputVector.size() + 1;
    for(auto i = 0u; i < outputVector.size(); i++)
    {
        outputVector[i] = weightsMatrix[i * rowSize];   // TODO maybe do it at the end?
    }

    for(auto i = 0u; i < inputVector.size(); i += 8)
    {
        auto x1 = _mm256_set1_ps(inputVector[i]);
        auto x2 = _mm256_set1_ps(inputVector[i + 1]);
        auto x3 = _mm256_set1_ps(inputVector[i + 2]);
        auto x4 = _mm256_set1_ps(inputVector[i + 3]);
        auto x5 = _mm256_set1_ps(inputVector[i + 4]);
        auto x6 = _mm256_set1_ps(inputVector[i + 5]);
        auto x7 = _mm256_set1_ps(inputVector[i + 6]);
        auto x8 = _mm256_set1_ps(inputVector[i + 7]);

        for(auto k = 0u; k < outputVector.size(); k += 8)
        {
            auto z = _mm256_loadu_ps(&outputVector[k]);    // TODO think of making it aligned
            auto w1 = _mm256_loadu_ps(&weightsMatrix[k * rowSize + i + 1]);
            auto w2 = _mm256_loadu_ps(&weightsMatrix[(k + 1) * rowSize + i + 1]);
            auto w3 = _mm256_loadu_ps(&weightsMatrix[(k + 2) * rowSize + i + 1]);
            auto w4 = _mm256_loadu_ps(&weightsMatrix[(k + 3) * rowSize + i + 1]);
            auto w5 = _mm256_loadu_ps(&weightsMatrix[(k + 4) * rowSize + i + 1]);
            auto w6 = _mm256_loadu_ps(&weightsMatrix[(k + 5) * rowSize + i + 1]);
            auto w7 = _mm256_loadu_ps(&weightsMatrix[(k + 6) * rowSize + i + 1]);
            auto w8 = _mm256_loadu_ps(&weightsMatrix[(k + 7) * rowSize + i + 1]);

            transpose8_ps(w1, w2, w3, w4, w5, w6, w7, w8);  // TODO maybe can arrange those data to be already transposed?

            auto xw1 = _mm256_mul_ps(x1, w1);
            auto xw2 = _mm256_mul_ps(x2, w2);
            auto xw3 = _mm256_mul_ps(x3, w3);
            auto xw4 = _mm256_mul_ps(x4, w4);
            auto xw5 = _mm256_mul_ps(x5, w5);
            auto xw6 = _mm256_mul_ps(x6, w6);
            auto xw7 = _mm256_mul_ps(x7, w7);
            auto xw8 = _mm256_mul_ps(x8, w8);

            auto xw12 = _mm256_add_ps(xw1, xw2);
            auto xw34 = _mm256_add_ps(xw3, xw4);
            auto xw56 = _mm256_add_ps(xw5, xw6);
            auto xw78 = _mm256_add_ps(xw7, xw8);
            auto xw1234 = _mm256_add_ps(xw12, xw34);
            auto xw5678= _mm256_add_ps(xw56, xw78);
            auto xw12345678= _mm256_add_ps(xw1234, xw5678);

            auto r = _mm256_add_ps(z, xw12345678);

            _mm256_storeu_ps(&outputVector[k], r);
        }
    }
}
