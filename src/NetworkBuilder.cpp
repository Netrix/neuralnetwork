#include "NetworkBuilder.hpp"

NotNull<BinaryNodeBuilder> NetworkBuilder::setRootNode(BinaryNode, std::string const& operation)
{
    auto l_builder = m_storage.createBinaryNodeBuilder(operation);
    m_root = l_builder;
    return l_builder;
}
