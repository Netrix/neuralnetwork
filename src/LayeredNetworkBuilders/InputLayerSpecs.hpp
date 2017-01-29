#pragma once

#include <string>

struct InputLayerSpecs
{
    InputLayerSpecs(std::size_t numInputs)
        : numInputs(numInputs)
    {}

    std::size_t numInputs; // TODO add check for numNeurons > 0
};
