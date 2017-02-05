#include <iostream>
#include <vector>
#include <memory>
#include <cassert>
#include <random>
#include <iomanip>
#include "Utils/NotNull.hpp"
#include "NodeSpecs.hpp"
#include "NodeBuilders/NodeBuilder.hpp"
#include "NodeBuilders/BinaryNodeBuilder.hpp"
#include "BuilderStorage.hpp"
#include "NetworkBuilder.hpp"
#include "LayeredNetworkBuilder.hpp"
#include "LayeredNetworkBuilders/FullyConnectedLayerSpecs.hpp"
#include "LayeredNetworkBuilders/FullyConnectedLayerBuilder.hpp"
#include "LayeredNetworkBuilders/InputLayerSpecs.hpp"
#include "Utils/MathVectorAdapter.hpp"
#include "StreamOperators.hpp"
#include "Datasets/MnistLoader.hpp"
#include <set>
#include "NormalDistributionGenerator.hpp"
#include "MnistPreprocessedDataSet.hpp"
#include "LearnUtils.hpp"
#include "PassThroughLayerNodeFactories/ReLULayer.hpp"

int main()
{
    std::string imagesPath = "../../../data/train-images-idx3-ubyte";
    std::string labelsPath = "../../../data/train-labels-idx1-ubyte";

    auto mnistDataset = MnistPreprocessedDataSet<float>(loadMnistDataset(imagesPath, labelsPath));
    std::cout << mnistDataset.getInputSampleSize() << " " << mnistDataset.getNumSamples() << " " << mnistDataset.getOutputSampleSize() << std::endl;

    LayeredNetworkBuilder layeredNetworkBuilder;
    auto outLayer = layeredNetworkBuilder.setOutputLayer(FullyConnectedLayerSpecs{
                                                             std::make_unique<ReLULayerNodeFactory<BNN_TYPE>>(), mnistDataset.getOutputSampleSize()});
    auto hiddenLayer = outLayer->setInputLayer(FullyConnectedLayerSpecs{
                                                   std::make_unique<ReLULayerNodeFactory<BNN_TYPE>>(), 32});
    hiddenLayer->setInputLayer(InputLayerSpecs{mnistDataset.getInputSampleSize()});
    auto network = layeredNetworkBuilder.buildBackPropagationNetwork(0.01f);

    network->setVariables(NormalDistributionGenerator<BNN_TYPE>(17, 0, 1e-1));

    using namespace std::chrono;
    auto start = steady_clock::now();

    BNN_TYPE errorSum{};
    for(auto i = 0u; i < 100u; ++i)
    {
        errorSum = learnEpochParallel(layeredNetworkBuilder, network, mnistDataset, 256, 0.01f, i);
        std::cout << "epoch: " << i << " errorSum: " << errorSum <<  std::endl;

    }

    auto end = steady_clock::now();

    std::cout << "Time taken: " << duration_cast<seconds>(end - start).count() << "s. errorSum: " << errorSum <<  std::endl;

    // TODO
    // 4. abstract backprop
    // 5. Cross validation 1:10
    // 6. Model saving/loading to/from files
    // 7. Weights saving/loading for model
    //
    // zero-centering data! mean centering
    // Shuffle training examples at each new epoch
    // Normalize input variables (u,o) = (0,1), where u=0

    // im2col for convolution

    /* gradient check
     * http://uvadlc.github.io/lectures/lecture2.pdf
     *
     * Most dangerous part for new modules -> get gradients wrong
     * Compute gradient analytically
     * Compute gradient computationally
     * Compare (difference should be in 10^-4, 10^-7)
*/
}
