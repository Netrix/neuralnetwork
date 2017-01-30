#pragma once

#include <string>
#include <cassert>

struct InputLayerSpecs
{
    InputLayerSpecs(std::size_t numInputs)
        : numInputs(numInputs)
    {
        assert(numInputs > 0);
    }

    std::size_t numInputs;
};
