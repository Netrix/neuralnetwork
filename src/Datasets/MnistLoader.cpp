#include "MnistLoader.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cassert>

namespace
{

struct alignas(4) MnistLabelsHeader
{
    int32_t magic;
    int32_t numLabels;
};

struct alignas(4) MnistImagesHeader
{
    int32_t magic;
    int32_t numImages;
    int32_t numRows;
    int32_t numColumns;
};

int32_t convertBigToLittleEndian(int32_t value)
{
    return ((value & 0xFF000000) >> 24)
        | ((value & 0xFF0000) >> 8)
        | ((value & 0xFF00) << 8)
        | ((value & 0xFF) << 24);
//    return (value & 0xFF000000);
}

} // namespace


MnistDataset loadMnistDataset(std::string const& imagesFilePath, std::string const& labelsFilePath)
{
    // Labels
    std::ifstream labelsFile(labelsFilePath);

    MnistLabelsHeader labelsHeader{};
    labelsFile.read(reinterpret_cast<char*>(&labelsHeader), sizeof(labelsHeader));
    labelsHeader.magic = convertBigToLittleEndian(labelsHeader.magic);
    labelsHeader.numLabels = convertBigToLittleEndian(labelsHeader.numLabels);

    assert(labelsHeader.magic == 0x801 && "Invalid magic value"); // TODO change it to exception

    std::vector<uint8_t> labelData(labelsHeader.numLabels);
    labelsFile.read(reinterpret_cast<char*>(labelData.data()), labelData.size());

    // Images
    std::ifstream imagesFile(imagesFilePath);

    MnistImagesHeader imagesHeader{};
    imagesFile.read(reinterpret_cast<char*>(&imagesHeader), sizeof(imagesHeader ));
    imagesHeader.magic = convertBigToLittleEndian(imagesHeader.magic);
    imagesHeader.numColumns = convertBigToLittleEndian(imagesHeader.numColumns);
    imagesHeader.numRows = convertBigToLittleEndian(imagesHeader.numRows);
    imagesHeader.numImages = convertBigToLittleEndian(imagesHeader.numImages);

    assert(imagesHeader.magic == 0x803 && "Invalid magic value"); // TODO change it to exception

    std::vector<uint8_t> imagesData(imagesHeader.numRows * imagesHeader.numColumns * imagesHeader.numImages);
    imagesFile.read(reinterpret_cast<char*>(imagesData.data()), imagesData.size());

    assert(imagesHeader.numImages == labelsHeader.numLabels && "Number of labels must match number of images"); // TODO change it to exception

    MnistDataset dataset{};
    dataset.imageData = std::move(imagesData);
    dataset.labels = std::move(labelData);
    dataset.imageWidth = imagesHeader.numColumns;
    dataset.imageHeight = imagesHeader.numRows;

    return dataset;
}
