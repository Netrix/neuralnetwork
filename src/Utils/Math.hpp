#pragma once
#include "ArrayView.hpp"

void vectorMatrixMultiplyFloat(ArrayView<float const> inputVector,
                               ArrayView<float const> weightsMatrix,
                               ArrayView<float> outputVector);


void vectorMatrixMultiplyUnalignedFloat4(ArrayView<float const> inputVector,
                                         ArrayView<float const> weightsMatrix,
                                         ArrayView<float> outputVector);

void vectorMatrixMultiplyUnalignedFloat8(ArrayView<float const> inputVector,
                                         ArrayView<float const> weightsMatrix,
                                         ArrayView<float> outputVector);
