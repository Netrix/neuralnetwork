#pragma once

#include <string>

struct FullyConnectedLayerSpecs
{
    std::size_t numNeurons; // TODO add check for numNeurons > 0
    std::string activation;
};
