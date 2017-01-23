#pragma once
#include <string>
#include <memory>
#include <vector>

struct MnistDataset
{
    uint32_t imageWidth;
    uint32_t imageHeight;
    std::vector<uint8_t> labels;
    std::vector<uint8_t> imageData;
};

MnistDataset loadMnistDataset(std::string const& images, std::string const& labels);
