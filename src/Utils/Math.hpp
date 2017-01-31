#pragma once
#include "ArrayView.hpp"

void vectorMatrixMultiplyFloat(ArrayView<float const> inputVector,
                               ArrayView<float const> inputMatrix,
                               ArrayView<float> outputVector);


void vectorMatrixMultiplyUnalignedFloat4(ArrayView<float const> inputVector,
                                         ArrayView<float const> inputMatrix,
                                         ArrayView<float> outputVector);
